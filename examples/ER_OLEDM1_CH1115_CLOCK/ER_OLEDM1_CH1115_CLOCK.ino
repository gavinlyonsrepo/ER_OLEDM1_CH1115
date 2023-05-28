/*!
	@file  ER_OLEDM1_CH1115_CLOCK.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing  example of a clock. just a simple demo. Bitmaps and Shared screen shown.
	@author Gavin Lyons

	@note
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-# This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
	@test
		-# Clock Demo
		-# Shared buffer, Multiple screens (2 off) spilt into top and bottom
*/

// two shared screens sharing one buffer
// ________________________
// |      Icons screen    |
// |______________________|
// |      Time screen     |
// |______________________|
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
ERMCH1115_SharedBuffer  topHalf(halfScreenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT/2, 0, 0);
ERMCH1115_SharedBuffer bottomHalf(halfScreenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT/2, 0, MYOLEDHEIGHT/2);


// ********* BITMAP Test data Section **********
const PROGMEM uint8_t Signal816[16]  = //mobile signal 16x8px
{
  0x03, 0x05, 0x09, 0xff, 0x09, 0x05, 0xf3, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0xfe, 0x00, 0xff, 0x00
};

const PROGMEM uint8_t Msg816[16]  =  //message ,'msg', 16x8px
{
  0x00, 0x00, 0x00, 0xff, 0x85, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x85, 0xff, 0x00, 0x00, 0x00
};

const PROGMEM uint8_t Bat816[16]  =   // 'battery', 16x8px
{
  0x00, 0x00, 0x7e, 0x42, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xff, 0x00
};

const PROGMEM uint8_t Bluetooth88[8]  =   // 'bluetooth', 8x8px
{
  0x00, 0x42, 0x24, 0xff, 0x99, 0x5a, 0x24, 0x00
};

const PROGMEM uint8_t GPRS88[8]  =  // 'gprs88', 8x8px
{ 
  0xc3, 0x81, 0x3c, 0x42, 0x52, 0x34, 0x81, 0xc3
};

const PROGMEM uint8_t Alarm88[8] =  // 'alarm', 8x8px
{
  0x83, 0xbd, 0x42, 0x4a, 0x52, 0x52, 0xbd, 0x83
};

// *** Test timing variables *****
unsigned long previousMillis = 0;  // will store last time  was updated:
const long interval = 1000;           // interval  (milliseconds)

// ************* SETUP ***************
void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0xC1, 0); // Fill the screen with a pattern ,  splash-screen effect
  delay(1500);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen
}

// *********** MAIN LOOP ******************
void loop()
{
  DisplayTopBar();
  while (1)
  {
    DisplayText();
  }

}
// *********** END OF MAIN ***********

// Section: functions

void DisplayTopBar()
{
  myOLED.ActiveBufferPtr =  &topHalf;   

  myOLED.OLEDclearBuffer(); // Clear the buffer

  myOLED.setDrawBitmapAddr(true); // for Bitmap Data Vertical  addressed
  myOLED.drawBitmap(4, 0, Signal816, 16, 8, OLED_WHITE, OLED_BLACK);
  myOLED.drawBitmap(24, 0, Bluetooth88, 8, 8, OLED_WHITE, OLED_BLACK);
  myOLED.drawBitmap(40, 0, Msg816, 16, 8, OLED_WHITE, OLED_BLACK);
  myOLED.drawBitmap(64, 0, GPRS88, 8, 8, OLED_WHITE, OLED_BLACK);
  myOLED.drawBitmap(90, 0, Alarm88, 8, 8, OLED_WHITE, OLED_BLACK);
  myOLED.drawBitmap(112, 0, Bat816, 16, 8, OLED_WHITE, OLED_BLACK);
  myOLED.OLEDupdate();
}

void DisplayText()
{

  myOLED.ActiveBufferPtr =  &bottomHalf;   
  myOLED.OLEDclearBuffer(); // Clear the buffer

  char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);

  uint8_t sec = 55;
  uint8_t Hour = 12;
  uint8_t Min = 35;

  while (1)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      sec++;
      if (sec == 60)
      {
        Min = Min + 1;
        sec = 0;
        if (Min == 60)
        {
          Hour =  Hour + 1;
          Min = 0;
          if (Hour == 24)
          {
            Hour = 0;
            Min = 0;
            sec = 0;
          }
        }
      }

      myOLED.drawChar(0, 1 ,  value[Hour / 10], OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(16, 1 , value[Hour % 10], OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(32, 1 , ':', OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(48, 1 , value[Min / 10], OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(66, 1 , value[Min % 10], OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(80, 1 , ':', OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(96, 1 , value[sec / 10], OLED_WHITE, OLED_BLACK, 3);
      myOLED.drawChar(112, 1 , value[sec % 10], OLED_WHITE, OLED_BLACK, 3);

      myOLED.OLEDupdate();
    }
  }
}
