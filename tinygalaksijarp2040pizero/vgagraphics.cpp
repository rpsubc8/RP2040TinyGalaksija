//
//  https://vanhunteradams.com/Pico/VGA/VGA.html
//

#include "gbConfig.h" 
#ifdef use_lib_vga

 #include <stdio.h>
 #include <stdlib.h>
 #include "pico/stdlib.h"
 #include "hardware/pio.h"
 #include "hardware/dma.h"
 // Our assembled programs:
 // Each gets the name <pio_filename.pio.h>
 #include "vgahsyncpio.h"
 #include "vgavsyncpio.h"
 #include "vgargbpio.h"
 // Header file
 #include "vgagraphics.h"
 // Font file
 #include "vgaglcdfont.h"

 // VGA timing constants
 #define H_ACTIVE 655    // (active + frontporch - 1) - one cycle delay for mov
 #define V_ACTIVE 479    // (active - 1)
 #define RGB_ACTIVE 319  // (horizontal active)/2 - 1

// Length of the pixel array, and number of DMA transfers
const unsigned int pixels = screenWidth * screenHeight;
#define TXCOUNT pixels / 2          // Total pixels / 2. The total size of the buffer
#define DMATXCOUNT screenWidth / 2  // Cantidad de transferencias DMA = Largo de la scanline
const int QVGALastLine = 240;  //La cantidad de lineas de los gráficos. Se usa para pasar la info al PIO (si se cambia se mueve la imagen)

// Pixel color array that is DMA's to the PIO machines and
// a pointer to the ADDRESS of this color array.
// Note that this array is automatically initialized to all 0's (black)
//unsigned char __attribute__((aligned(4))) vga_data_array[TXCOUNT]; //76800 bytes (640x240 div 2)
//unsigned char vga_data_array[TXCOUNT]; //76800 bytes (640x240 div 2)
unsigned char *vga_data_array; //reserved with malloc SETUP INO 76800 bytes (640x240 div 2)
volatile unsigned char* address_pointer_array = &vga_data_array[0];
#ifdef use_lib_vga_one_buffer
#else
 unsigned char vga_data_array_next[TXCOUNT];
#endif 

// Bit masks for drawPixel routine
#define TOPMASK 0b11000111
#define BOTTOMMASK 0b11111000

// For drawLine
#define swap(a, b) \
  { \
    short t = a; \
    a = b; \
    b = t; \
  }

// For writing text
#define tabspace 4  // number of spaces for a tab

// For accessing the font library
#define pgm_read_byte(addr) (*(const unsigned char*)(addr))

// For drawing characters
unsigned short cursor_y, cursor_x, textsize;
char textcolor, textbgcolor, wrap;

// DMA channels - 0 sends color data, 1 reconfigures and restarts 0
int rgb_dma_pio = dma_claim_unused_channel(true);
int rgb_dma_cb = dma_claim_unused_channel(true);

//uint32_t SaveDividerState; // saved integer divider state
volatile uint32_t currentFrame;  // frame counter

volatile int currentScanLine;  // current processed scan line 0... (next displayed scan line)

// QVGA DMA handler - called on end of every scanline
void __not_in_flash_func(QVgaLine)() 
{
 unsigned int auxOffs;
 // Clear the interrupt request for DMA control channel
 dma_hw->ints0 = (1u << rgb_dma_pio);
 // update DMA control channel and run it

 // save integer divider state
 //hw_divider_save_state(&SaveDividerState);

 // increment scanline (1..)
 currentScanLine++;             // new current scanline
 if (currentScanLine >= 480) {  // last scanline?
  currentFrame++;              // increment frame counter
  currentScanLine = 0;         // restart scanline
 }

 #ifdef use_lib_vga_one_buffer 
  //DMATXCOUNT 640 div 2
  //address_pointer_array = &vga_data_array[DMATXCOUNT * (currentScanLine>>1)]; //Quito fallo visual primera linea
  auxOffs= (currentScanLine>>1); //Quito fallo visual primera linea
  auxOffs= (auxOffs<<8)+(auxOffs<<6); //(auxoffs div 2) x 256 + x 64 eq 320. 480 lineas dibujo mitad 240
  address_pointer_array = &vga_data_array[auxOffs];
 #else
  address_pointer_array = &vga_data_array[DMATXCOUNT * (currentScanLine + 1 >> 1)];
 #endif 

  // restore integer divider state
  //hw_divider_restore_state(&SaveDividerState);
}

void initVGA() {
  // Choose which PIO instance to use (there are two instances, each with 4 state machines)
  PIO pio = pio0;

  // Our assembled program needs to be loaded into this PIO's instruction
  // memory. This SDK function will find a location (offset) in the
  // instruction memory where there is enough space for our program. We need
  // to remember these locations!
  //
  // We only have 32 instructions to spend! If the PIO programs contain more than
  // 32 instructions, then an error message will get thrown at these lines of code.
  //
  // The program name comes from the .program part of the pio file
  // and is of the form <program name_program>
  uint hsync_offset = pio_add_program(pio, &hsync_program);
  uint vsync_offset = pio_add_program(pio, &vsync_program);
  uint rgb_offset = pio_add_program(pio, &rgb_program);

  // Manually select a few state machines from pio instance pio0.
  uint hsync_sm = 0;
  uint vsync_sm = 1;
  uint rgb_sm = 2;

  // Call the initialization functions that are defined within each PIO file.
  // Why not create these programs here? By putting the initialization function in
  // the pio file, then all information about how to use/setup that state machine
  // is consolidated in one place. Here in the C, we then just import and use it.
  hsync_program_init(pio, hsync_sm, hsync_offset, HSYNC);
  vsync_program_init(pio, vsync_sm, vsync_offset, VSYNC);
  rgb_program_init(pio, rgb_sm, rgb_offset, RED_PIN);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // ============================== PIO DMA Channels =================================================
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  // Channel Zero (sends color data to PIO VGA machine)
  dma_channel_config c0 = dma_channel_get_default_config(rgb_dma_pio);  // default configs
  channel_config_set_transfer_data_size(&c0, DMA_SIZE_8);               // 8-bit txfers
  channel_config_set_read_increment(&c0, true);                         // yes read incrementing
  channel_config_set_write_increment(&c0, false);                       // no write incrementing
  channel_config_set_dreq(&c0, DREQ_PIO0_TX2);                          // DREQ_PIO0_TX2 pacing (FIFO)
  channel_config_set_chain_to(&c0, rgb_dma_cb);                         // chain to other channel

  dma_channel_configure(
    rgb_dma_pio,        // Channel to be configured
    &c0,                // The configuration we just created
    &pio->txf[rgb_sm],  // write address (RGB PIO TX FIFO)
    &vga_data_array,    // The initial read address (pixel color array)
    DMATXCOUNT,         // Number of transfers; in this case each is 1 byte.
    false               // Don't start immediately.
  );

  // Channel One (reconfigures the first channel)
  dma_channel_config c1 = dma_channel_get_default_config(rgb_dma_cb);  // default configs
  channel_config_set_transfer_data_size(&c1, DMA_SIZE_32);             // 32-bit txfers
  channel_config_set_read_increment(&c1, false);                       // no read incrementing
  channel_config_set_write_increment(&c1, false);                      // no write incrementing
  channel_config_set_chain_to(&c1, rgb_dma_pio);                       // chain to other channel

  dma_channel_configure(
    rgb_dma_cb,                          // Channel to be configured
    &c1,                                 // The configuration we just created
    &dma_hw->ch[rgb_dma_pio].read_addr,  // Write address (channel 0 read address)
    &address_pointer_array,              // Read address (POINTER TO AN ADDRESS)
    1,                                   // Number of transfers, in this case each is 4 byte
    false                                // Don't start immediately.
  );

  // enable DMA channel IRQ0
  dma_channel_set_irq0_enabled(rgb_dma_pio, true);
  // set DMA IRQ handler
  irq_set_exclusive_handler(DMA_IRQ_0, QVgaLine);
  irq_set_enabled(DMA_IRQ_0, true);
  // set highest IRQ priority
  irq_set_priority(DMA_IRQ_0, 0);
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  // Initialize PIO state machine counters. This passes the information to the state machines
  // that they retrieve in the first 'pull' instructions, before the .wrap_target directive
  // in the assembly. Each uses these values to initialize some counting registers.
  pio_sm_put_blocking(pio, hsync_sm, H_ACTIVE);
  pio_sm_put_blocking(pio, vsync_sm, V_ACTIVE);
  pio_sm_put_blocking(pio, rgb_sm, RGB_ACTIVE);


  // Start the two pio machine IN SYNC
  // Note that the RGB state machine is running at full speed,
  // so synchronization doesn't matter for that one. But, we'll
  // start them all simultaneously anyway.
  pio_enable_sm_mask_in_sync(pio, ((1u << hsync_sm) | (1u << vsync_sm) | (1u << rgb_sm)));

  // Start DMA channel 0. Once started, the contents of the pixel color array
  // will be continously DMA's to the PIO machines that are driving the screen.
  // To change the contents of the screen, we need only change the contents
  // of that array.
  dma_start_channel_mask((1u << rgb_dma_pio));
}


// A function for drawing a pixel with a specified color.
// Note that because information is passed to the PIO state machines through
// a DMA channel, we only need to modify the contents of the array and the
// pixels will be automatically updated on the screen.
void drawPixel(short x, short y, char color) 
{
  // Range checks
  if ((x < screenWidth - 1) && (x > 0) && (y > 0) && (y < screenHeight - 1)) {

      // Which pixel is it?
      int pixel = ((screenWidth * y) + x);

      // Is this pixel stored in the first 3 bits
      // of the vga data array index, or the second
      // 3 bits? Check, then mask.
      #ifdef use_lib_vga_one_buffer
       if (pixel & 1) 
       {       
        vga_data_array[pixel >> 1] = (vga_data_array[pixel >> 1] & TOPMASK) | (color << 3);
       }
       else
       {
        vga_data_array[pixel >> 1] = (vga_data_array[pixel >> 1] & BOTTOMMASK) | (color);
       }      
      #else
       if (pixel & 1) 
       {       
        vga_data_array_next[pixel >> 1] = (vga_data_array_next[pixel >> 1] & TOPMASK) | (color << 3);
       }
       else
       {
        vga_data_array_next[pixel >> 1] = (vga_data_array_next[pixel >> 1] & BOTTOMMASK) | (color);
       }
      #endif 
    }
}

void clearScreen()
{
 #ifdef use_lib_vga_one_buffer
  for (int i = 0; i < TXCOUNT; i++) 
  {
   vga_data_array[i] = 0;
  } 
 #else
  for (int i = 0; i < TXCOUNT; i++) 
  {
   vga_data_array_next[i] = 0;
  }
 #endif 
}

void nextFrame() 
{
 #ifdef use_lib_vga_one_buffer  
 #else
  for (int i = 0; i < TXCOUNT; i++) 
  {
   vga_data_array[i] = vga_data_array_next[i];
  }
 #endif
}

void drawVLine(short x, short y, short h, char color) 
{
 for (short i = y; i < (y + h); i++) 
 {
  drawPixel(x, i, color);
 }
}

void drawHLine(short x, short y, short w, char color)
{
 for (short i = x; i < (x + w); i++)
 {
  drawPixel(i, y, color);
 }
}

// Bresenham's algorithm - thx wikipedia and thx Bruce!
void drawLine(short x0, short y0, short x1, short y1, char color) {
  /* Draw a straight line from (x0,y0) to (x1,y1) with given color
    Parameters:
         x0: x-coordinate of starting point of line. The x-coordinate of
             the top-left of the screen is 0. It increases to the right.
         y0: y-coordinate of starting point of line. The y-coordinate of
             the top-left of the screen is 0. It increases to the bottom.
         x1: x-coordinate of ending point of line. The x-coordinate of
             the top-left of the screen is 0. It increases to the right.
         y1: y-coordinate of ending point of line. The y-coordinate of
             the top-left of the screen is 0. It increases to the bottom.
         color: 3-bit color value for line
  */
  short steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  short dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  short err = dx / 2;
  short ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// Draw a rectangle
void drawRect(short x, short y, short w, short h, char color) {
  /* Draw a rectangle outline with top left vertex (x,y), width w
    and height h at given color
    Parameters:
         x:  x-coordinate of top-left vertex. The x-coordinate of
             the top-left of the screen is 0. It increases to the right.
         y:  y-coordinate of top-left vertex. The y-coordinate of
             the top-left of the screen is 0. It increases to the bottom.
         w:  width of the rectangle
         h:  height of the rectangle
         color:  16-bit color of the rectangle outline
    Returns: Nothing
  */
  drawHLine(x, y, w, color);
  drawHLine(x, y + h - 1, w, color);
  drawVLine(x, y, h, color);
  drawVLine(x + w - 1, y, h, color);
}

void drawRectCenter(short x, short y, short w, short h, char color) {
  drawRect(x - w / 2, y - h / 2, w, h, color);
}

void drawCircle(short x0, short y0, short r, char color) {
  /* Draw a circle outline with center (x0,y0) and radius r, with given color
    Parameters:
         x0: x-coordinate of center of circle. The top-left of the screen
             has x-coordinate 0 and increases to the right
         y0: y-coordinate of center of circle. The top-left of the screen
             has y-coordinate 0 and increases to the bottom
         r:  radius of circle
         color: 16-bit color value for the circle. Note that the circle
             isn't filled. So, this is the color of the outline of the circle
    Returns: Nothing
  */
  short f = 1 - r;
  short ddF_x = 1;
  short ddF_y = -2 * r;
  short x = 0;
  short y = r;

  drawPixel(x0, y0 + r, color);
  drawPixel(x0, y0 - r, color);
  drawPixel(x0 + r, y0, color);
  drawPixel(x0 - r, y0, color);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void drawCircleHelper(short x0, short y0, short r, unsigned char cornername, char color) {
  // Helper function for drawing circles and circular objects
  short f = 1 - r;
  short ddF_x = 1;
  short ddF_y = -2 * r;
  short x = 0;
  short y = r;

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void fillCircle(short x0, short y0, short r, char color) {
  /* Draw a filled circle with center (x0,y0) and radius r, with given color
    Parameters:
         x0: x-coordinate of center of circle. The top-left of the screen
             has x-coordinate 0 and increases to the right
         y0: y-coordinate of center of circle. The top-left of the screen
             has y-coordinate 0 and increases to the bottom
         r:  radius of circle
         color: 16-bit color value for the circle
    Returns: Nothing
  */
  drawVLine(x0, y0 - r, 2 * r + 1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

void fillCircleHelper(short x0, short y0, short r, unsigned char cornername, short delta, char color) {
  // Helper function for drawing filled circles
  short f = 1 - r;
  short ddF_x = 1;
  short ddF_y = -2 * r;
  short x = 0;
  short y = r;

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if (cornername & 0x1) {
      drawVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
      drawVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
    }
    if (cornername & 0x2) {
      drawVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
      drawVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
    }
  }
}

// Draw a rounded rectangle
void drawRoundRect(short x, short y, short w, short h, short r, char color) {
  /* Draw a rounded rectangle outline with top left vertex (x,y), width w,
    height h and radius of curvature r at given color
    Parameters:
         x:  x-coordinate of top-left vertex. The x-coordinate of
             the top-left of the screen is 0. It increases to the right.
         y:  y-coordinate of top-left vertex. The y-coordinate of
             the top-left of the screen is 0. It increases to the bottom.
         w:  width of the rectangle
         h:  height of the rectangle
         color:  16-bit color of the rectangle outline
    Returns: Nothing
  */
  // smarter version
  drawHLine(x + r, y, w - 2 * r, color);          // Top
  drawHLine(x + r, y + h - 1, w - 2 * r, color);  // Bottom
  drawVLine(x, y + r, h - 2 * r, color);          // Left
  drawVLine(x + w - 1, y + r, h - 2 * r, color);  // Right
  // draw four corners
  drawCircleHelper(x + r, y + r, r, 1, color);
  drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
  drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
  drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

// Fill a rounded rectangle
void fillRoundRect(short x, short y, short w, short h, short r, char color) {
  // smarter version
  fillRect(x + r, y, w - 2 * r, h, color);

  // draw four corners
  fillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
  fillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}


// fill a rectangle
void fillRect(short x, short y, short w, short h, char color) {
  /* Draw a filled rectangle with starting top-left vertex (x,y),
     width w and height h with given color
    Parameters:
         x:  x-coordinate of top-left vertex; top left of screen is x=0
                 and x increases to the right
         y:  y-coordinate of top-left vertex; top left of screen is y=0
                 and y increases to the bottom
         w:  width of rectangle
         h:  height of rectangle
         color:  3-bit color value
    Returns:     Nothing
  */

  for (int i = x; i < (x + w); i++) {
    for (int j = y; j < (y + h); j++) {
      drawPixel(i, j, color);
    }
  }
}

// Draw a character
void drawChar(short x, short y, unsigned char c, char color, char bg, unsigned char size) {
  char i, j;
  if ((x >= screenWidth) ||        // Clip right
      (y >= screenHeight) ||       // Clip bottom
      ((x + 6 * size - 1) < 0) ||  // Clip left
      ((y + 8 * size - 1) < 0))    // Clip top
    return;

  for (i = 0; i < 6; i++) {
    unsigned char line;
    if (i == 5)
      line = 0x0;
    else
      line = pgm_read_byte(font + (c * 5) + i);
    for (j = 0; j < 8; j++) {
      if (line & 0x1) {
        if (size == 1)  // default size
          drawPixel(x + i, y + j, color);
        else {  // big size
          fillRect(x + (i * size), y + (j * size), size, size, color);
        }
      } else if (bg != color) {
        if (size == 1)  // default size
          drawPixel(x + i, y + j, bg);
        else {  // big size
          fillRect(x + i * size, y + j * size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}


void setTextCursor(short x, short y) {
  /* Set cursor for text to be printed
    Parameters:
         x = x-coordinate of top-left of text starting
         y = y-coordinate of top-left of text starting
    Returns: Nothing
  */
  cursor_x = x;
  cursor_y = y;
}

void setTextSize(unsigned char s) {
  /*Set size of text to be displayed
    Parameters:
         s = text size (1 being smallest)
    Returns: nothing
  */
  textsize = (s > 0) ? s : 1;
}

void setTextColor(char c) {
  // For 'transparent' background, we'll set the bg
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

void setTextColor2(char c, char b) {
  /* Set color of text to be displayed
    Parameters:
         c = 16-bit color of text
         b = 16-bit color of text background
  */
  textcolor = c;
  textbgcolor = b;
}

void setTextWrap(char w) {
  wrap = w;
}


void tft_write(unsigned char c) {
  if (c == '\n') {
    cursor_y += textsize * 8;
    cursor_x = 0;
  } else if (c == '\r') {
    // skip em
  } else if (c == '\t') {
    int new_x = cursor_x + tabspace;
    if (new_x < screenWidth) {
      cursor_x = new_x;
    }
  } else {
    drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
    cursor_x += textsize * 6;
    if (wrap && (cursor_x > (screenWidth - textsize * 6))) {
      cursor_y += textsize * 8;
      cursor_x = 0;
    }
  }
}

 void writeString(char* str) {
  /* Print text onto screen
    Call tft_setTextCursor(), tft_setTextColor(), tft_setTextSize()
     as necessary before printing
  */
  while (*str) {
    tft_write(*str++);
  }
 }

// Check if alive ???????????????
 int getPixel(short x, short y) 
 {
  int index = (((640 * (y << 1)) + (x << 1))) >> 1;

  return (vga_data_array[index] & 1);
 }


#endif
