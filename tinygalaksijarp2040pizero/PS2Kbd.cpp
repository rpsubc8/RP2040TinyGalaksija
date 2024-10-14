#include "gbConfig.h"
#include "gbGlobals.h"
//#include "testvga.h" //Ya no se necesita
//#include "hardware.h"
//#include "keys.h" //Ya no se necesita
#include "PS2Kbd.h"


#define gb_max_keymap 32
#define gb_max_keymap32 8
volatile unsigned char gb_keymap[gb_max_keymap]; //256 DIV 8 = 32 bytes packet bit
volatile unsigned int *gb_keymap32=(unsigned int *)gb_keymap;

unsigned char keyup = 0;

//#define DEBUG_LOG_KEYSTROKES 1


static unsigned char gb_kb_bitcount = 0;
static unsigned char gb_kb_incoming = 0;
static unsigned int gb_kb_prev_ms = 0; 

void __not_in_flash_func()kb_interruptHandler()
{
 unsigned int now_ms;
 unsigned char n, val;

 //if (digitalRead(KEYBOARD_CLK) == 1)
 if digitalReadFast2040(KEYBOARD_CLK)
 {
  return;
 }

 val= digitalReadFast2040(KEYBOARD_DATA); //val = digitalRead(KEYBOARD_DATA);
 now_ms = millis(); 
 if ((now_ms - gb_kb_prev_ms) > 250)
 {
  gb_kb_bitcount = 0;
  gb_kb_incoming = 0;
 }
 gb_kb_prev_ms = now_ms;
 n = gb_kb_bitcount - 1;
 if (n <= 7)
 {
  gb_kb_incoming |= (val << n);
 }
 gb_kb_bitcount++;
 if (gb_kb_bitcount == 11)
 {
  if (keyup == 1) 
  {//Se libera tecla pasa a 1   
   if (((gb_keymap[(gb_kb_incoming>>3)]>>(gb_kb_incoming & 0x07)) & 0x01) == 0)
   {
    gb_keymap[(gb_kb_incoming>>3)] |= (1<<(gb_kb_incoming & 0x07));
   }
   else
   {
    //Serial.println("WARNING: Keyboard cleaned");    
    for (unsigned char gg = 0; gg < gb_max_keymap32; gg++)
    {
     gb_keymap32[gg]=(unsigned int)0xFFFFFFFF;
    }     
   }
   keyup = 0;
  }
  else
  {//Se pulsa tecla pasa a 0
   gb_keymap[(gb_kb_incoming>>3)] &= ((~(1<<(gb_kb_incoming & 0x07))) & 0xFF);
  }

  //#ifdef DEBUG_LOG_KEYSTROKES
  // #ifdef use_lib_log_serial
  //  Serial.printf("PS2Kbd[%s]: %02X\r\n", keyup ? " up " : "down", gb_kb_incoming);
  // #endif    
  //#endif

  keyup= (gb_kb_incoming == 240) ? 1 : 0;
  
  gb_kb_bitcount = 0;
  gb_kb_incoming = 0;
 }
}


void kb_begin()
{
 memset((void *)gb_keymap, 0xFF, sizeof(gb_keymap));
  
 pinMode(KEYBOARD_DATA, INPUT_PULLUP);
 pinMode(KEYBOARD_CLK, INPUT_PULLUP);
 digitalWrite(KEYBOARD_DATA, true);
 digitalWrite(KEYBOARD_CLK, true);
      
 attachInterrupt(digitalPinToInterrupt(KEYBOARD_CLK), kb_interruptHandler, FALLING);
}


// Check if key is pressed and clean it
unsigned char checkAndCleanKey(unsigned char scancode)
{
 unsigned char auxId= scancode>>3; //DIV 8
 unsigned char auxOffs= scancode & 0x07; //MOD 8

 unsigned char valor= ((gb_keymap[auxId])>>auxOffs)&0x01;

 if (valor == 0)
 {
  gb_keymap[auxId] |= (1<<auxOffs);

  return 1;     
 }
 return 0;
 
}

//*****************************************
unsigned char checkKey(unsigned char scancode)
{
 unsigned char auxId= scancode>>3; //DIV 8
 unsigned char auxOffs= scancode & 0x07; //MOD 8

 unsigned char valor= (~((gb_keymap[auxId])>>auxOffs))&0x01;
  
 return valor;
}

//******************************************
void ClearKeyboard()
{
 for (unsigned char i = 0; i < gb_max_keymap32; i++)
 {      
  gb_keymap32[i]=(unsigned int)0xFFFFFFFF;
 }
}
