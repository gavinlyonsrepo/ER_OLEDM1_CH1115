
// Example file name : ER_OLEDM1_CH1115_ONEBUF.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of Single buffer mode. 
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option SINGLE_BUFFER must be selected and only this option. 
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// ****************************** 

#include "ER_OLEDM1_CH1115.hpp"


#define OLEDcontrast 0x80 //Contrast 00 to FF , 0x80 is default. user adjust

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI

ERMCH1115  myOLED(DC, RES, CS); // instate object , CD, RST, CS

int count = 50;

// ************* SETUP ***************
void setup() 
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the LCD
  delay(1000);
}

// ************** MAIN LOOP ***********
void loop() 
{
  DisplayText();
}

// ************** END OF MAIN ***********

void DisplayText() 
{
   uint8_t  screenBuffer[1024];  // create a full screen buffer (128 * 64/8) 
   myOLED.buffer = (uint8_t*) &screenBuffer;  // Assign the pointer to the buffer
   myOLED.OLEDclearBuffer(); // Clear the buffer
   myOLED.setTextSize(1);
   myOLED.setTextColor(FOREGROUND);
   while(1)
   {
    myOLED.setCursor(0, 24);
    myOLED.print(F("Single Buffer"));
    myOLED.setCursor(0,40);
    myOLED.print(count);
    myOLED.OLEDupdate();   // Writes to the buffer 
    delay(1000);
    myOLED.OLEDclearBuffer();
    count= count + 10;  
   }
}
