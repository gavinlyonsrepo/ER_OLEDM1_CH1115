
// Example file name : ER_OLEDM1_CH1115_SWSPI.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of software SPI  mode
// only difference for user is the constructor used when you instantiate the object and pin definations
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option MULTI_BUFFER must be selected and only this option.
// (3) This is for software  SPI for hardware SPI see all other examples.
// ******************************
#include "ER_OLEDM1_CH1115.hpp"

#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
#define OLEDcontrast 0x80 //Contrast 00 to FF , 0x80 is default. user adjust

// GPIO 5-wire SPI interface
#define CS 10  // GPIO pin number pick any you want
#define DC 9 // "
#define RES 8 // "
#define SCL 12 // "
#define SDA  11 // "

ERMCH1115  myOLED(DC, RES, CS, SCL, SDA); 

// Vars for the test
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch

// ************* SETUP ***************
void setup() {
  delay(50);
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0); // Fill the screen with zeros
  startTime = millis();
}

// ************** MAIN LOOP ***********
void loop() {
  // define a buffer to cover whole screen
  uint8_t  screenBuffer[MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)]; // 1024 bytes = 128 * 64/8

  MultiBuffer window;   // Declare a multibuffer struct 
  // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&window, screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);

  // Call a function to display text, pass struct
  DisplayText(&window);
}

// ************** END OF MAIN ***********

void DisplayText(MultiBuffer* screen)
{
  int count = 0;
  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.ActiveBuffer =  screen;
  myOLED.OLEDclearBuffer(); // Clear the buffer
  while (1)
  {
    myOLED.OLEDclearBuffer();
    myOLED.setCursor(20, 20);
    myOLED.print(F("Software SPI"));
    myOLED.setCursor(20, 30);
    myOLED.print(F("speed test:"));
    myOLED.setCursor(20, 50);
    if (count < 1000)
    {
      myOLED.print(count);
    } else
    {
      elapsedTime =   millis() - startTime;
      myOLED.print("Time Taken:");
      myOLED.print(elapsedTime / 1000L);
    }
    delay(1);
    myOLED.OLEDupdate();  // Write to the buffer
    if (count == 1000)
    {
      while (1) {
        delay(1000);
      }; //test finished
    }
    count ++;
  }
}
