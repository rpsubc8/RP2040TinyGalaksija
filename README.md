# RP2040 Tiny Galaksija
Galaksija emulator Waveshare RP2040 pizero
<center><img src='https://raw.githubusercontent.com/rpsubc8/RP2040TinyGalaksija /main/preview/rp2040pizero.jpg'></center>
Port I had made from TinyESP32 to RP2040 with VGA and HDMI. Based on the x86 emulator by Miodrag Jevremovic, Tomaž Šolc and Peter Bakota.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyGalaksija'>https://github.com/rpsubc8/ESP32TinyGalaksija</a><br><br>

Using use_lib_hdmi in gbConfig.h (hdmi connector on waveshare board):<br>

| HDMI      | GPIO        |
| --------- | ------------|
| sm_tmds   | 0, 1, 2     |
| pins_tmds | 26, 24, 22  |
| pins_clk  | 28          |

<br><br>
Using use_lib_vga in gbConfig.h:<br>

| VGA GPIO  | Description  |
| --------- | ------------ |
| 18        | RED          | 
| 19        | GREEN        |
| 20        | BLUE         |
| 16        | HSync        |
| 17        | VSync        |

<br>
In this connector we have:<br><br>

| VGA         | Description  |
| ----------- | ------------ |
| 1           | RED          | 
| 2           | GREEN        |
| 3           | BLUE         |
| 13          | HSYNC        |
| 14          | VSYNC        |
| 5,6,7,8,11  | GROUND       |

Some modern monitors may need 5v (very low amperage) on pin 9, which in the current schematic is not connected (N/C).<br>



<br><br>
<h1>PS/2 keyboard USB C</h1>
If we have a Waveshare PiZero board, we can use the PIO-USB connector, i.e. the central one, which is located between the HDMI and the power supply.<br>
From this USB C connector, we can use a USB to USB C converter.<br>
In the gbConfig.h we must choose the option use_lib_keyboard_ps2usb, which will use GPIO 6 and 7.

| PS2 GPIO  | Description |
| --------- | ----------- |
|  6        | CLK  (D+)   |
|  7        | Data (D-)   |

For some emulators, when using the native HID protocol via USB, the keyboard must be connected to the external connector, while the board is powered by the central connector (PIO-USB). But in this case, you are using the PS/2 protocol, so you must connect to the central PIO-USB and power it on the external USB.
<br><br>


<h1>Description</h1>
<ul>
 <li>Arduino IDE 1.8.16</li>
 <li>Board Waveshare RP2040 pizero</li>
 <li>Tested with Earle F.Philhower,III 2.6.4 and Earle F.Philhower,III 3.9.3</li>
 <li>HDMI picoDVI fork adafruit version 1.0.0</li>
 <li>Adafruit GFX library</li>
 <li>Adafruit BusIO library</li>
 <li>VGA library (Hunter Adams and San Tarcisio mod)</li>
 <li>PS2 library (ps2kbdlib michalhol mod)</li>
 <li>A variety of PS/2 keyboards, as well as USB keyboards with PS/2 conversion allow 3.3v power supply. Be sure to work with 3.3v. Never power the keyboard at 5v. In case you are using the PIO-USB USB C connector, you can work with 5V. Make sure you know what you are doing, and if in doubt, just don't go ahead.</li>
 <li>Although 3 GPIO's are used for VGA, since only 1 bit of colour (black and white) is used, one of the 3 colour GPIO outputs can be used at each input of the VGA monitor.</li>
 <li>No overclock voltage HDMI (1.05v). By default RP2040 runs at 1.10v and 133 Mhz. For HDMI it is required to overclock to 1.25v and 250 Mhz. For HDMI, I have done an undervolt, to be more conservative, i.e. I have left it at 1.05v, being configurable in gbConfig.h. If it doesn't look good, you can go higher.</li> 
 <li>Activate the option: Optimize Even More (-02) or (-03) for HDMI</li>
</ul>



<br><br>
<h1>Tool data2h</h1>
I have created a very basic tool (win32) to convert .GTP and .GAL files into .h in ready mode to be processed by the emulator.<br>
It is recommended to have short file names. Additionally, the tool cuts to 32 characters to display in the OSD.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyGalaksija/main/preview/previewWinData2h.gif'></center>
We just have to leave the .GAL and .GTP files in the <b>input/GAL</b> folder and <b>input/GTP</b> run the <b>data2h.exe</b> file , so that an output will be generated in the <b>output/dataFlash</b> directory.<a href='https://github.com/rpsubc8/ESP32TinyGalaksija/tree/main/esp32/tools/data2h'>Tool data2h</a><br><br>
<pre>
 input/
  gal/
  gtp/
 output/
  dataFlash/
   gal/
   gtp/ 
</pre>
Later we must copy the <b>dataFlash</b> directory to the <b>galaksija</b> project, overwriting the previous dataFlash folder. It is recommended to clean the project and compile again.<br>
This tool is very simple, and does not control errors, so it is recommended to leave the files with very simple names and as simple as possible.<br>
Since the source code is available, it can be compiled for Linux or for Android under Termux. In Termux we have to install the <b>gcc</b> or <b>clang</b> package and compile:<br>
<pre>
 gcc -s data2h.cpp -odata2h.a
</pre>
It must be done from the home data directory of the Android device, so if we do it in any other directory, the <b>data2h.a</b> created will never be able to be executed, unless the device is rooted.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyGalaksija/main/preview/previewTermuxData2h.gif'></center><br><br>




<h1>Precompile version</h1>
Versions VGA, HDMI, with PS/2 to USB C converter (ps2usb) are available.<br><br>
<a href='https://github.com/rpsubc8/RP2040TinyGalaksija/tree/main/precompile'>https://github.com/rpsubc8/RP2040TinyGalaksija/tree/main/precompile</a><br><br>
I have left a version called <b>galaksijahdmips2usbvolt120</b>, where 1.2 volts is used, for a more stable overclock on those boards (FLASH speed problem) and HDMI monitors that may give problems.
