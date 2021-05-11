
![ OLED ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/oled.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Installation](#installation)
  * [Hardware](#hardware)
  * [Features](#features)
  * [Files](#files)
  * [Tested_MCU](#tested_MCU)
  * [Ports](#ports)
  * [Issues](#issues)
  
Overview
--------------------
* Name : ER_OLEDM1_CH1115
* Title : Library to support the ER-OLEDM1.09-1 128X64 OLED Display Module driven by the CH1115 controller for the Arduino eco-system.
* Description : 

1. Arduino library.      
2. Inverse colour, vertical rotate, sleep, fade effect, horizontal scroll and contrast control. 
3. Extended ASCII scalable font. 
4. Graphics class included.
5. 3 different modes: Multi-buffer , single buffer , no buffer.
6. Bitmaps supported.
7. Hardware & software SPI options

* Author: Gavin Lyons
* Arduino IDE: 1.8.10

Output
-----------------------------

Output Screenshots, From left to right, top to bottom.

1. Full screen bitmap displayed 
2. Multi buffer mode screen divided into two horizontal buffers
3. Multi buffer mode screen divided into vertical buffers, clock demo.
4. Different size and type of fonts 
5. Available ASCII font printed out 0-127
6. Extended ASCII font printed out 128-255  

![ output ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/output.jpg)

Installation
------------------------------

The library is included in the official Arduino library manger and the optimum way to install it is 
using the library manager which can be opened by the *manage libraries* option in Arduino IDE. 

See link below for instruction for this and for the other methods too.

[Installing Additional Arduino Libraries guide](https://www.arduino.cc/en/Guide/Libraries)

Hardware
----------------------------

CH1115 is a single-chip CMOS OLED driver with controller for organic light emitting diode dot-matrix graphic display system. CH1115 consists of 128 segments, 64 commons that can support a maximum display resolution of 128 X 64. It is designed for Common Cathode type OLED panel. ER-OLEDM1.09-1W-SPI is a White 1.09" OLED Display Panel with Breakout Board. This module is a combination of the two.(controller and OLED)

| pin no  | pin name | pin desc |
|---|---|---|
| 1 | Gnd | Ground |
| 2 | VCC | voltage supply |
| 3 | SCL | Serial clock input |
| 4 | SDA | Serial data input |
| 5 | RES | This pin is reset signal input. When the pin is low, initialization of the chip is executed. |
| 6 | DC | This pin is Data or Command control pin. |
| 7 | CS | This pin is the chip select input. The chip is enabled for MCU comms only when CS# is pulled low. |

**VCC**
The CH1115 controller chip is a 3.3V device but the ERM LCD module has a "662k" 3.3V regulator at back.
So the ERM LCD module VCC will run at 5V as well if this is present. It was always run it at 3.3 vcc during testing.

**Logic lines**
The logic lines where ALWAYS connected to 3.3 Volts logic during all testing of library. 
Are the logic lines 5 volt tolerant? Most likely , did not test as had only two test devices. 
Although the CH1115 chip is a 3.3V device  , The datasheet for the entire OLED module
says 5V is acceptable but 3.3 typical. 

| Datasheet Data  | max | Typ | min |
|---| ---| --- | --- |
| OLED logic voltage Absolute ratings |  5.5 | n/a |-0.3 |
| OLED logic voltage Characteristics | 5.0 |  3.3 | 3.0 |
 

This wiring Diagram from the manufacturer showing hardware setup connected to a 
3.3 volt system MCU

![ wiring ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/wiring.jpg)

Features
-------------------------

*SPI*

Hardware and software SPI. Two different class constructors. User can pick the relevant constructor, see examples files. Hardware SPI is recommended, far faster and more reliable but Software SPI allows for more flexible GPIO selection. When running Software SPI it may be necessary on very fast high frequency MCU's to change the ERMCH1115_HIGHFREQ_DELAY define, It is a microsecond delay by default it is at 0. All the hardware SPI settings are defined in the header file and can be easily changed if necessary. 

*buffers*

3 buffer modes 

1. MULTI_BUFFER (default)
2. SINGLE_BUFFER 
3. NO_BUFFER , Text only,  light weight. 

To switch between modes, user must make a change to the USER BUFFER OPTION SECTION  at top of ER_OLEDM1_CH1115.h file.  Pick ONE option and one option ONLY. The example files at top, say which option to pick. If wrong option is picked, example files will not work or maybe even compile. Bitmaps can still be written directly to screen in NO_BUFFER mode but no graphics possible.

*fonts*

The ASCII font( ER_OLEDM1_CH1115_font.h file) is truncated by two defines ( USER OPTION section)
to save memory space, if you wish to include the entire font simply comment these defines in. 

1. UC_FONT_MOD_ONE (increase 150 bytes) First 0-30 ASCII characters
2. UC_FONT_MOD_TWO (increase 640 bytes) extended ASCII 127-255

The scale-able font is a  5 by 7 ASCII font with padding added by SW. So 7 by 8 in effect. This means: 128/7 * 64/8 = 144 characters. 

*bitmaps*

Bitmaps are written directly to screen, not buffer, Updating the buffer will overwrite them(unless bitmap set to buffer) so to share screen with text and graphics best to divide screen into buffers using multi buffer mode,  See examples files. Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) , use vertical addressing draw mode. 

*User adjustments*

When the user calls OLEDbegin() to start OLED they can specify a contrast setting from 0x00 to 0xFF. Datasheet says 0x80 is default. User can also change contrast on the fly.
Screen can be disabled to enter a sleep type mode where OLED draws 500uA.
Screen pixel colour can be inverted and also screen can be vertically rotated. 

There is a "fade or breath display effect". Whose parameters(time brightness) can be adjusted by passing data to function see "OLEDfadeEffect" function header  in .cpp and datasheet for details.
default is 0x81.

There is a  Horizontal scroll effect. Whose parameters: Time-interval , direction , mode,
can be adjusted by passing data to function see "OLEDscrollSetup" function header in .cpp and datasheet for details. defaults are : 6 frames , right , continuous mode.

*Functions*

Detailed information on the functions can be found in comment headers in the X.cpp  files and a list of them in keywords.txt. 

Files
-------------------

X = ER_OLEDM1_CH1115 in tables below

| Src Files| Desc |
| ------ | ------ |
| X.h | library header file  |
| X.cpp |  library  source file  |
| X_graphics.h | graphics header file |
| X_graphics.cpp |  graphics source file |
| X_graphics_font.h | graphics  font  file |

The example files are setup for an arduino UNO/NANO for the pin connections used 
for other MCU's during testing see extras folder, GPIO_MCU_used.txt file.

| Examples files ino  | Desc | Buffer mode |
| ------ | ------ |  ------ |
| X_HELLO | Helloworld | MULTI_BUFFER | 
| X_BITMAP | Shows use of bitmaps  | Several, see setup notes in file  |
| X_CLOCK | clock MULTI_BUFFER demo | Several, see setup notes in file |
| X_GRAPHICS |  Shows use of graphics   | MULTI_BUFFER |
| X_TXT | Shows use of text in buffer mode   | MULTI_BUFFER |
| X_MBUF | Shows use of multi buffer mode | MULTI_BUFFER |
| X_MISC | Shows misc functions, rotate , scroll , sleep invert etc | MULTI_BUFFER |
| X_NOBUF | Shows use of no buffer text only mode | NO_BUFFER  |
| X_ONEBUF| Shows use of single buffer mode | SINGLE_BUFFER | 
| X_SWSPI | Shows use of software SPI | MULTI_BUFFER | 


Tested_MCU
-------------------------------

Tested on following MCUs.

	1. Arduino  UNO & NANO v3
	2. ESP8266 
	3. ESP32 
	4. STM32 "blue pill"


Ports
-----------------------------

[Raspberry pi , C++](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_RPI)


Issues 
--------------------------

Issues with v1.0.0 , these are corrected in repo but  still exist in v1.0.0 tarball.

1. Typo in single buffer example file  ER_OLEDM1_CH1115_ONEBUF.ino, in line assigning buffer size : screenBuffer[1537];  should be screenBuffer[1024]; . Example file still works, just assigns more memory than it should. 
