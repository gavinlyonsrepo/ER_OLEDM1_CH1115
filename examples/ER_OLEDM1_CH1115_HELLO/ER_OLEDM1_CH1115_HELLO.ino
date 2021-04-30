
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

#include "ER_OLEDM1_CH1115.h"

#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. user adjust
#define myOLEDheight 64
#define myOLEDwidth  128

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
// GPIO pin number SCK(UNO 13) , HW SPI , SCK

ERMCH1115  myOLED(DC, RES, CS); // instantiate  an object 

void setup() {
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0);
}

void loop() {

  // define a buffer to cover whole screen 
  uint8_t  screenBuffer[myOLEDwidth * (myOLEDheight/8)]; // 1024 bytes = 128 * 64/8

  // Declare a buffer struct
  MultiBuffer mybuffer;

  // Intialise struct 
  mybuffer.screenbitmap = (uint8_t*) &screenBuffer; // point it to the buffer
  mybuffer.width = myOLEDwidth ;
  mybuffer.height = myOLEDheight;
  mybuffer.xoffset = 0;
  mybuffer.yoffset = 0;

  // Assign address of struct to be the active buffer pointer 
  myOLED.ActiveBuffer = &mybuffer;

  myOLED.OLEDclearBuffer();   // Clear active buffer 

  myOLED.setTextColor(FOREGROUND);
  while (1)
  {
    myOLED.setCursor(0, 32);
    myOLED.print(F("Hello world"));
    myOLED.OLEDupdate();  //write to active buffer
    delay(5000);
  }
}
