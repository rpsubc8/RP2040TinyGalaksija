#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H

 //Important, is little endian (do not modify)
 #define LSB_FIRST 

 //Fix register std ISO C++17
 #define register

 //Fix modos de video quitarlo
 #define video_mode_360x200x70hz_bitluni 0 
 #define video_mode_360x200x70hz_bitluni_apll_fix 1
 #define video_mode_vga320x200x70hz_bitluni 2
 #define video_mode_vga320x200x70hz_fabgl 3
 #define video_mode_vga320x200x70hz_bitluni_apll_fix 4
 #define video_mode_vga320x240x60hz_bitluni 5
 #define video_mode_vga320x240x60hz_fabgl 6
 #define video_mode_vga320x240x60hz_bitluni_apll_fix 7

 //Keyboard (select one option)
 //Keyboard GPIO external real PS2 connector [CLK(4) DATA(5)]
 //#define use_lib_keyboard_ps2
 //Keyboard usb board (waveshare) with adapter PS2 to usb, usb to usbC [CLK(6)D+ DATA(7)D-] PIO-USB
 #define use_lib_keyboard_ps2usb
   

 //Solo 1 buffer 76800 bytes (no nextframe)
 #define use_lib_vga_one_buffer

 //Use hdmi waveshare rp2040 pizero (select one option)
 //#define use_lib_hdmi
 #define use_lib_vga

 //voltage overclock HDMI warning (select one option) 1.10v is default RP2040
 #define VREG_VSEL VREG_VOLTAGE_1_05
 //#define VREG_VSEL VREG_VOLTAGE_1_10
 //#define VREG_VSEL VREG_VOLTAGE_1_20
 //#define VREG_VSEL VREG_VOLTAGE_1_25
  

 //Delay boot keyboard
 #define gb_delay_keyboard_init_ms 500
 //Delay set voltage stable
 #define gb_delay_hdmi_voltage_init_ms 10


 //use bilutni custom fast (do not modify)
 #define use_lib_tinybitluni_fast

 //Not use double numbers (IEEE not fpu) calculate vga frequency
 //#define use_lib_fix_double_precision

 //Debug i2s bitluni vga frequency
 #define use_lib_debug_i2s

 //Video mode boot (select only one option)
 //#define use_lib_boot_vga_360x200x70hz_bitluni_3bpp
 //#define use_lib_boot_vga_360x200x70hz_bitluni_apll_3bpp
 //#define use_lib_boot_vga_320x200x70hz_bitluni_3bpp
 //#define use_lib_boot_vga_320x200x70hz_fabgl_3bpp
 //#define use_lib_boot_vga_320x200x70hz_bitluni_apll_3bpp
 #define use_lib_boot_vga_320x240x60hz_bitluni_3bpp
 //#define use_lib_boot_vga_320x240x60hz_fabgl_3bpp
 //#define use_lib_boot_vga_320x240x60hz_bitluni_apll_3bpp
 //#define use_lib_boot_vga_360x200x70hz_bitluni_6bpp
 //#define use_lib_boot_vga_360x200x70hz_bitluni_apll_6bpp
 //#define use_lib_boot_vga_320x200x70hz_bitluni_6bpp
 //#define use_lib_boot_vga_320x200x70hz_fabgl_6bpp
 //#define use_lib_boot_vga_320x200x70hz_bitluni_apll_6bpp
 //#define use_lib_boot_vga_320x240x60hz_bitluni_6bpp
 //#define use_lib_boot_vga_320x240x60hz_fabgl_6bpp
 //#define use_lib_boot_vga_320x240x60hz_bitluni_apll_6bpp 
 

 //Time to select video mode at startup (ms)
 #define use_lib_boot_time_select_vga 500

 //Important (do not modify)
 #define use_lib_skip_FD_error

 //Put ROM in flash (free 8192 bytes RAM)
 #define use_lib_rom_flash
 
 //MEMORY uses 8 KB instead of 64 KB RAM
 #define use_lib_ram_8KB


 //log trace
 #define use_lib_log_serial

 //keyboard
 //#define use_lib_keyboard_uart

 //timeout read millis
 #define use_lib_keyboard_uart_timeout 0

 //log keyboard serial
 //#define use_lib_log_keyboard_uart


 //Proyect ArduinoDroid
 //#gb_use_lib_compile_arduinodroid



 //Keyboard
 #ifdef use_lib_keyboard_ps2
  #define KEYBOARD_CLK 4
  #define KEYBOARD_DATA 5
 #else
  #ifdef use_lib_keyboard_ps2usb
   #define KEYBOARD_CLK 6
   #define KEYBOARD_DATA 7
  #endif 
 #endif





 //Internal (do not modify)
 #ifdef use_lib_boot_vga_360x200x70hz_bitluni_3bpp
  #define use_lib_vga8colors
  #define use_lib_vga360x200x70hz_bitluni
 #else
  #ifdef use_lib_boot_vga_360x200x70hz_bitluni_apll_3bpp
   #define use_lib_vga8colors
   #define use_lib_vga360x200x70hz_bitluni_apll_fix
  #else
   #ifdef use_lib_boot_vga_320x200x70hz_bitluni_3bpp
    #define use_lib_vga8colors
    #define use_lib_vga320x200x70hz_bitluni
   #else
    #ifdef use_lib_boot_vga_320x200x70hz_fabgl_3bpp
     #define use_lib_vga8colors
     #define use_lib_vga320x200x70hz_fabgl
    #else
     #ifdef use_lib_boot_vga_320x200x70hz_bitluni_apll_3bpp
      #define use_lib_vga8colors
      #define use_lib_vga320x200x70hz_bitluni_apll_fix
     #else
      #ifdef use_lib_boot_vga_320x240x60hz_bitluni_3bpp
       #define use_lib_vga8colors
       #define use_lib_vga320x240x60hz_bitluni
      #else
       #ifdef use_lib_boot_vga_320x240x60hz_fabgl_3bpp
        #define use_lib_vga8colors
        #define use_lib_vga320x240x60hz_fabgl
       #else
        #ifdef use_lib_boot_vga_320x240x60hz_bitluni_apll_3bpp
         #define use_lib_vga8colors
         #define use_lib_vga320x240x60hz_bitluni_apll_fix
         #else
          #ifdef use_lib_boot_vga_360x200x70hz_bitluni_6bpp           
           #define use_lib_vga360x200x70hz_bitluni
          #else 
           #ifdef use_lib_boot_vga_360x200x70hz_bitluni_apll_6bpp
            #define use_lib_vga360x200x70hz_bitluni_apll_fix
           #else
            #ifdef use_lib_boot_vga_320x200x70hz_bitluni_6bpp
             #define use_lib_vga320x200x70hz_bitluni
            #else
             #ifdef use_lib_boot_vga_320x200x70hz_fabgl_6bpp
              #define use_lib_vga320x200x70hz_fabgl
             #else
              #ifdef use_lib_boot_vga_320x200x70hz_bitluni_apll_6bpp
               #define use_lib_vga320x200x70hz_bitluni_apll_fix
              #else
               #ifdef use_lib_boot_vga_320x240x60hz_bitluni_6bpp
                #define use_lib_vga320x240x60hz_bitluni
               #else
                #ifdef use_lib_boot_vga_320x240x60hz_fabgl_6bpp
                 #define use_lib_vga320x240x60hz_fabgl
                #else
                 #ifdef use_lib_boot_vga_320x240x60hz_bitluni_apll_6bpp
                  #define use_lib_vga320x240x60hz_bitluni_apll_fix
                 #endif
                #endif 
               #endif 
              #endif
             #endif 
            #endif
           #endif
          #endif
        #endif
       #endif 
      #endif 
     #endif
    #endif
   #endif
  #endif
 #endif







/*
 ////Mode 3bits 8 colors
 //#define use_lib_vga8colors

 //Modo video 
 //Select one mode and deselect other modes
 //360x200 720x400 31.3 Khz 70.3 Hz freq:28322000 pixel_clock:14161000
 //#define use_lib_vga360x200x70hz_bitluni
 //360x200 720x400 31.3 Khz 70.3 Hz freq:28322000 pixel_clock:14161000 FIX PLL LOCK ESP32
 //#define use_lib_vga360x200x70hz_bitluni_apll_fix

 //320x200 720x400 31.4 Khz 70.0 Hz freq:25175000 pixel_clock:12587500
 //#define use_lib_vga320x200x70hz_bitluni
 //320x200 70Hz freq:12587500 funciona
 //#define use_lib_vga320x200x70hz_fabgl
 //320x200 720x400 31.4 Khz 70.0 Hz freq:25175000 pixel_clock:12587500 FIX PLL LOCK ESP32
 //#define use_lib_vga320x200x70hz_bitluni_apll_fix
 
 
 //320x240 640x480 31.4 Khz 60 Hz freq:25175000 pixel_clock:12587500 
 #define use_lib_vga320x240x60hz_bitluni
 //QVGA 320x240 60Hz freq:12600000 funciona
 //#define use_lib_vga320x240x60hz_fabgl
 //320x240 640x480 31.4 Khz 60 Hz freq:25175000 pixel_clock:12587500 FIX PLL LOCK ESP32
 //#define use_lib_vga320x240x60hz_bitluni_apll_fix
*/
 

 #if defined(use_lib_vga360x200x70hz_bitluni) || defined(use_lib_vga360x200x70hz_bitluni_apll_fix)
  #define use_lib_360x200
 #else
  #if defined(use_lib_vga320x200x70hz_bitluni) || defined(use_lib_vga320x200x70hz_fabgl) || defined(use_lib_vga320x200x70hz_bitluni_apll_fix)
   #define use_lib_320x200
  #else
   #if defined(use_lib_vga320x240x60hz_bitluni) || defined(use_lib_vga320x240x60hz_fabgl) || defined(use_lib_vga320x240x60hz_bitluni_apll_fix)
    #define use_lib_320x240
   #endif
  #endif
 #endif


 /*No se usa
 //Modo video
 //#define use_lib_360x200
 //#define use_lib_320x200
 #define use_lib_320x240
 */
 

 //#define use_lib_cont_call
 //#define use_lib_skip_fps
 

 

 
#endif
 
