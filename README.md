[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

![url OLED image ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/oled.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Installation](#installation)
  * [Hardware](#hardware)
  * [Software](#software)
  * [Tested_MCU](#tested_MCU)

Overview
--------------------
* Name : ER_OLEDM1_CH1115
* Title : Library to support the ER-OLEDM1.09-1 128X64 OLED Display Module driven by the CH1115 controller for the Arduino eco-system.
* Description : 

1. Arduino eco-system library.      
2. Invert colour, vertical rotate, sleep, fade effect, horizontal scroll and contrast control  functions supported.
3. 8 ASCII fonts included.
4. Graphics support included.
5. Multi Screen, single shared buffer mode.
6. Bitmaps supported.
7. Hardware & software SPI options

* Author: Gavin Lyons
* Arduino IDE: 1.8.10

Output
-----------------------------

Output Screenshots, From left to right, top to bottom.

1. Full screen bitmap displayed 
2. Shared Screen mode screen divided into two horizontal Screens with one buffer
3. Shared Screen mode screen divided into vertical Screens with one buffer, clock demo.
4. Different size and type of fonts 
5. Available ASCII font printed out 0-127
6. Extended ASCII font printed out 128-255  
7. Font 1-4 
8. Font 7

![ url output image ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/output.jpg)
![ url output image 2 ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_RPI/blob/main/extras/image/fontpic.jpg)

Installation
------------------------------

The library is included in the official Arduino library manger and the optimum way to install it is 
using the library manager which can be opened by the *manage libraries* option in Arduino IDE. 

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
| 7 | CS | This pin is chip select input. The chip is enabled for MCU comms  when CS is pulled low|

**VCC**
The CH1115 controller chip is a 3.3V device but the ERM LCD module has a "662k" 3.3V regulator at back. So the ERM OLED module VCC will also run at 5V. 

**Logic lines**
The logic lines where always connected to 3.3 Volts logic during all testing of library.
 The system can also run at 5 volts logic, the manufacture has instructional videos connected to 
 an  Arduino Mega. 
 
 This wiring Diagram from the manufacturer datasheet showing hardware setup connected to a 3.3 volt system MCU.

![ url wiring  image ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/wiring.jpg)

Software
-------------------------

**API**

The API (application programming interface) documentation is at link hosted on github pages and generated by Doxygen. 

[URL](https://gavinlyonsrepo.github.io/misc/software_docs/ER_OLEDM1_CH1115/index.html)

**SPI**

Hardware and software SPI. Two different class constructors. User can pick the relevant constructor, see examples files. Hardware SPI is recommended, far faster and more reliable but Software SPI allows for more flexible GPIO selection. When running Software SPI it may be necessary on very fast high frequency MCU's to change the ERMCH1115_HIGHFREQ_DELAY define, It is a microsecond delay by default it is at 0. All the hardware SPI settings are defined in the header file and can be easily changed if necessary. 

**buffers**

The library features a multi-screen shared buffer mode, In order to save data memory.

For example if user defines a buffer to cover the whole screen it takes 1024 bytes of data memory. Instead a user can create a buffer that covers half the screen 512 bytes then define two screens each pointing to the same buffer.
The user uses the ERMCH1115_SharedBuffer Class objects to define each screen
and the ActiveBufferPtr to switch between each screen. Multiple screens of same size can be created 
so OLED screen can be divided into thirds or quarters saving even more memory.
The disadvantage of this is the code is slightly more complicated and user can only write to one Screen at a time. If user does not want to use multi screen mode they can just define a screen to cover entire OLED screen. See example files for more detail.

**fonts**

There are eight fonts.
A print class is available to print out most passed data types.
The fonts 1-6 are a byte high(at text size 1) scale-able fonts, columns of padding added by SW.
Font 7-8 are special large numerical font  and cannot be scaled(just one size).  
Font 7-8 will print just numbers + semi-colons ,  if you print a float using print command
it will place a space and use a circle for a decimal point.

Font data table: 

| Font num | Font enum name | Font size xbyy |  ASCII range | Size in bytes |
| ------ | ------ | ------ | ------ |  ------ | 
| 1 | OLEDFontType_Default | 5x8 | ASCII 0 - 0xFF, Full Extended  | 1275 |
| 2 | OLEDFontType_Thick   | 7x8 |  ASCII  0x20 - 0x5A, no lowercase letters | 406 | 
| 3 | OLEDFontType_SevenSeg  | 4x8 | ASCII  0x20 - 0x7A | 360 |
| 4 | OLEDFontType_Wide | 8x8 |  ASCII 0x20 - 0x5A, no lowercase letters| 464 |
| 5 | OLEDFontType_Tiny | 3x8 | ASCII  0x20 - 0x7E | 285 |
| 6 | OLEDFontType_Homespun  | 7x8 | ASCII  0x20 - 0x7E |  658 |
| 7 | OLEDFontType_Bignum | 16x32 | ASCII 0x30-0x3A ,Numbers + : . only | 704 |
| 8 | OLEDFontType_Mednum | 16x16 | ASCII 0x30-0x3A , Numbers + : . only | 352 |

By default only Font 1 is commented in and ready to go to save memory.
So to use a non-default Font (2-8), two steps.

1. Comment in the respective define at top of library header file ER_OLEDM1_CH1115_font.hpp in the USER FONT OPTION ONE section.
2. Call SetFontNum function and pass it enum label of respective font.  

*font mods*

The default ASCII font (font 1) is an extended font, 0-255 characters.
If you do not need characters 127-255 and wish to save memory space:
In  file ER_OLEDM1_CH1115_font.cpp in the USER FONT OPTION TWO section
Simply comment this define out. 

1. UC_FONT_MOD_TWO (save 640 bytes) extended ASCII 127-255

You can also remove the first 30 characters of default font if not needed but user will need to change  ASCII offset also. This will save a further 150 bytes.

*bitmaps*

There is a few different ways of displaying bitmaps, 

| Num | Method |    Data addressing | Note |
| ------ | ------ | ------- |  ------ |  
| 1 | OLEDBitmap() | Vertical |  Writes directly to screen , no buffer used. | 
| 2 | OLEDBuffer()  |   Vertical  |  Mostly for internal use ... mostly | 
| 3 | Multi buffer init  | Vertical  |  Can be used when initialising a MB | 
| 4 | drawBitmap() |   Vertical | default,  setDrawBitmapAddr(true) | 
| 5 | drawBitmap() |  Horizontal | setDrawBitmapAddr(false) |

See the bitmap example file for more details on each method. Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) , Bitmaps  should be defined in the program memory and buffers in the data memory, for methods 3 & 4 buffers can be initialised with bitmap data.

*User adjustments*

When the user calls OLEDbegin() to start OLED they can specify a contrast setting from 0x00 to 0xFF. Datasheet says 0x80 is default. User can also change contrast on the fly.
Screen can be disabled to enter a sleep type mode where OLED draws 500uA.
Screen pixel colour can be inverted and also screen can be vertically rotated. 

There is a "fade or breath display effect". Whose parameters(time brightness) can be adjusted by passing data to function see "OLEDfadeEffect" function header  in .cpp and datasheet for details.
default is 0x81.

There is a  Horizontal scroll effect. Whose parameters: Time-interval , direction , mode,
can be adjusted by passing data to function see "OLEDscrollSetup" function header in .cpp and datasheet for details. defaults are : 6 frames , right , continuous mode.

Files
-------------------

X = ER_OLEDM1_CH1115 in tables below

| Src Files | Description  |
| ------ | ------ |
| X.hpp | library header file  |
| X.cpp |  library  source file  |
| X_graphics.hpp | graphics header file |
| X_graphics.cpp |  graphics source file |
| X_graphics_font.hpp |  font file |
| X_graphics_font.cpp |  font data file |

The example files are setup for an arduino UNO/NANO 

| Examples files ino  | Description | 
| ------ | ------ |  
| X_HELLO | Basic usage | 
| X_MBUF | Shows use of shared buffer mode + FPS| 
| X_CLOCK | Shows use of shared buffer mode + clock demo| 
| X_MISC | Fonts + graphics & misc functions, rotate , scroll,  etc | 
| X_SWSPI | Shows use of software SPI | 
| X_BITMAP | Shows use of bitmaps  | 


Tested_MCU
-------------------------------

Tested on following MCUs. for the pin connections used 
during testing see extras folder, GPIO_MCU_used.txt file.

1. Arduino  UNO & NANO  v3  [Example](https://github.com/gavinlyonsrepo/RF_DATA_LINK)
2. ESP8266 
3. ESP32 
4. STM32 "blue pill"
5. Arduino Uno R4 Minima
