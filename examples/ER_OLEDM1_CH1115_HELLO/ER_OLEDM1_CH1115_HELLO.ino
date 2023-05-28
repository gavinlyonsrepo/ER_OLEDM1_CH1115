/*!
	@file  ER_OLEDM1_CH1115_HELLO.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use of hello world
	URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@test 
		Hello world
	@note 
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-#  This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
*/

#include "ER_OLEDM1_CH1115.hpp"

//Contrast 00 to FF , 0x80 is default. user adjust
#define OLEDcontrast 0x80 

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
// GPIO pin number SCK(UNO 13) , HW SPI , SCK

// Buffer setup
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
// Define a Buffer
uint8_t  screenBuffer[MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)]; 
// instantiate an OLED object
ERMCH1115  myOLED(DC, RES, CS); 
// instantiate an Shared buffer object , only one in this case to cover whole screen
ERMCH1115_SharedBuffer fullScreen(screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);

void setup() {
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
  myOLED.OLEDFillScreen(0x00, 0);
  myOLED.ActiveBufferPtr = &fullScreen;  // Assign Screen to be the active buffer pointer
  myOLED.OLEDclearBuffer();   
}

void loop() {
    myOLED.setCursor(20, 20);
    myOLED.print(F("Hello world"));
    myOLED.OLEDupdate();  // Update  active buffer
    delay(5000);
}
