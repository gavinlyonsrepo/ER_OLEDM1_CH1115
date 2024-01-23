/*!
	@file ER_OLEDM1_CH1115_SWSPI.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use of software SPI  mode
	only difference for user is the constructor used when you instantiate the object and pin definations
	@author Gavin Lyons
	@note
		-# (1) GPIO is for arduino UNO for other tested MCU see readme.
		-# (2) This is for software SPI for hardware SPI see all other examples.
	
	@test
		-# 601 Software SPI
*/
#include "ER_OLEDM1_CH1115.hpp"

//Contrast 00 to FF , 0x80 is default. user adjust
#define OLEDcontrast 0x80 
#define SWSPIGPIODelay 0 // uS Software SPi GPIO delay, zero by default

// GPIO 5-wire SW SPI interface
#define CS 10  // GPIO pin number pick any you want
#define DC 9 // "
#define RES 8 // "
#define SCL 12 // "
#define SDA  11 // "

// Buffer setup
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
#define FULLSCREEN (MYOLEDWIDTH  * (MYOLEDHEIGHT / 8))
// Define a Buffer
uint8_t screenBuffer[FULLSCREEN]; 

// instantiate an OLED object
ERMCH1115  myOLED(MYOLEDWIDTH, MYOLEDHEIGHT, DC, RES, CS, SCL, SDA); 
// instantiate an Shared buffer object , only one in this case to cover whole screen
ERMCH1115_SharedBuffer fullScreen(screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);

// Vars for the test
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch

// ************* SETUP ***************
void setup() {
  delay(50);
  myOLED.OLEDHighFreqDelaySet(SWSPIGPIODelay);
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0); // Fill the screen with zeros
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);
  myOLED.ActiveBufferPtr =  &fullScreen;
  startTime = millis();
}

// ************** MAIN LOOP ***********
void loop() {
  DisplayText();
}

// ************** END OF MAIN ***********

void DisplayText()
{
  int count = 0;
  myOLED.OLEDclearBuffer(); // Clear the buffer
  while (1)
  {
    myOLED.OLEDclearBuffer();
    myOLED.setCursor(20, 0);
    myOLED.print(F("Software SPI"));
    myOLED.setCursor(20, 10);
    myOLED.print(F("Speed test"));
    myOLED.setCursor(20, 20);
    myOLED.print(myOLED.OLEDHighFreqDelayGet());
    myOLED.setCursor(20, 30);
    if (count < 1000)
    {
      myOLED.print(count);
    } else
    {
      elapsedTime =   millis() - startTime;
      myOLED.setCursor(20, 40);
      myOLED.print("Time Taken:");
      myOLED.print(elapsedTime / 1000L);
    }
    delay(1);
    myOLED.OLEDupdate();  // Write to the buffer
    if (count == 1000)
    {
      while(1){delay(100);}; //test finished
    }
    count ++;
  }
}
