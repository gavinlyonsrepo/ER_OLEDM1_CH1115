
// Example file name : ER_OLEDM1_CH1115_MBUF.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of mulitple buffers.  In this case: two, divided vertically.
// The user can also divide horizontally and create as many buffers as they want.
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

ERMCH1115  myOLED(DC, RES, CS); //  object , DC, RST, CS


// vars for the test
static long previousMillis  = 0;
uint16_t count  = 0;
bool colour = 1;
// ************* SETUP ***************
void setup() {
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0);
  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setFontNum(OLEDFontType_Default);
}

// *********** MAIN LOOP ******************
void loop() {
  static long framerate = 0;
  uint8_t  screenBuffer[(MYOLEDWIDTH * (MYOLEDHEIGHT / 8)) / 2]; //(128 * 8)/2 = 512 bytes

  MultiBuffer left_side;
    // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&left_side, screenBuffer, MYOLEDWIDTH/2, MYOLEDHEIGHT, 0, 0);

  MultiBuffer right_side;
    // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&right_side, screenBuffer, MYOLEDWIDTH/2, MYOLEDHEIGHT, MYOLEDWIDTH/2, 0);

  while(1)
  {
    display_Left(&left_side, framerate, count);
    display_Right(&right_side);

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

// Function to display left hand side buffer
void display_Left(MultiBuffer* targetbuffer, long currentFramerate, int count)
{
  myOLED.ActiveBuffer = targetbuffer; // set target buffer object
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
  myOLED.print("Ver 1.3.2");
  myOLED.drawFastVLine(92, 0, 63, FOREGROUND);
  myOLED.OLEDupdate();
}

// Function to display right hand side buffer
void display_Right(MultiBuffer* targetbuffer)
{
  myOLED.ActiveBuffer = targetbuffer; // set target buffer object
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print(F("RHS buffer"));

  myOLED.fillRect(0, 10, 20, 20-(count/200), colour);
  myOLED.fillCircle(40, 20, count/200, !colour);
  myOLED.drawRoundRect(10, 40, 40, 20, 10, FOREGROUND);

  myOLED.OLEDupdate();
}
