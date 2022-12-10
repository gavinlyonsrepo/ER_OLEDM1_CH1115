
// Example file name : ER_OLEDM1_CH1115_HELLO.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of hellow world
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option MULTI_BUFFER must be selected
// and only this option. It is on by default.
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// ******************************

#include "ER_OLEDM1_CH1115.hpp"

#define OLEDcontrast 0x80 //Contrast 00 to FF , 0x80 is default. user adjust
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
// GPIO pin number SCK(UNO 13) , HW SPI , SCK

ERMCH1115  myOLED(DC, RES, CS); // instantiate  an object

void setup() {
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.setTextColor(FOREGROUND);
  myOLED.setFontNum(OLEDFontType_Default);
  myOLED.OLEDFillScreen(0x00, 0);
}

void loop() {

  // define a buffer to cover whole screen
  uint8_t  screenBuffer[MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)]; // 1024 bytes = 128 * 64/8

  MultiBuffer myStruct;   // Declare a multibuffer struct 
  // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&myStruct, screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);
  myOLED.ActiveBuffer = &myStruct;  // Assign struct to be the active buffer pointer

  myOLED.OLEDclearBuffer();   // Clear active buffer

  while (1)
  {
    myOLED.setCursor(20, 20);
    myOLED.print(F("Hello world"));
    myOLED.OLEDupdate();  // Update  active buffer
    delay(5000);
  }
}
