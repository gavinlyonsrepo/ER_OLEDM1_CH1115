
/*!
	@file ER_OLEDM1_CH1115_MBUF.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use of shared buffer multiple screen  In this case: two.
	@author Gavin Lyons
	@note
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-# This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
	@test
		-# Shared buffer, Multiple screens (2 off) spilt into left and right
		-# FPS test frame per second 
*/

// two shared screens sharing one buffer
//  ______________________
// | Left side | Right side|
// |           |           |
// |           |           |
// |___________|___________|
//
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
uint8_t  halfScreenBuffer[(MYOLEDWIDTH * (MYOLEDHEIGHT / 8)) / 2]; //(128 * 8)/2 = 512 bytes half screen 
// instantiate an OLED object
ERMCH1115  myOLED(DC, RES, CS); 
// instantiate two Shared buffer objects , one for each half of screen
ERMCH1115_SharedBuffer  leftSide(halfScreenBuffer, MYOLEDWIDTH/2, MYOLEDHEIGHT, 0, 0);
ERMCH1115_SharedBuffer rightSide(halfScreenBuffer, MYOLEDWIDTH/2, MYOLEDHEIGHT, MYOLEDWIDTH/2, 0);

// vars for the test
static long previousMillis  = 0;
uint16_t count  = 0;
bool colour = 1;
// ************* SETUP ***************
void setup() {
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0);
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
}

// *********** MAIN LOOP ******************
void loop() {
  static long framerate = 0;
  while(1)
  {
    display_Left(framerate, count);
    display_Right();

    framerate++;
    count++;
    if (count == 3000)
    {
      myOLED.OLEDPowerDown(); // Switch off OLED when test over
      while(1){delay(10);} // wait here for ever
    }
  }
}
// *********** END OF MAIN ***********

// Function to display left hand side screen
void display_Left(long currentFramerate, int count)
{
  myOLED.ActiveBufferPtr = &leftSide; // set Active buffer to left side screen address
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print(F("LHS Buffer"));

  myOLED.setCursor(0, 10);
  myOLED.print(F("512 bytes"));

  myOLED.setCursor(0, 20);
  myOLED.print(F("G Lyons"));

  myOLED.setCursor(0, 30);
  myOLED.print(count);
  // Values to count frame rate per second
  static long lastFramerate = 0;
  static uint16_t fps;
  unsigned long currentMillis = millis();

  if (currentMillis  - previousMillis  >= 1000) {
    fps = currentFramerate - lastFramerate;
    lastFramerate = currentFramerate ;
    previousMillis  = currentMillis;
    colour = !colour;
  }

  myOLED.setCursor(0, 40);
  myOLED.print(fps);
  myOLED.print(" fps");
  myOLED.setCursor(0, 50);
  myOLED.print("Ver 1.3.3");
  myOLED.drawFastVLine(92, 0, 63, OLED_WHITE);
  myOLED.OLEDupdate();
}

// Function to display right hand side screen
void display_Right()
{
  myOLED.ActiveBufferPtr = &rightSide; // set Active buffer to right side screen address
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print(F("RHS buffer"));

  myOLED.fillRect(0, 10, 20, 20-(count/200), colour);
  myOLED.fillCircle(40, 20, count/200, !colour);
  myOLED.drawRoundRect(10, 40, 40, 20, 10, OLED_WHITE);

  myOLED.OLEDupdate();
}
