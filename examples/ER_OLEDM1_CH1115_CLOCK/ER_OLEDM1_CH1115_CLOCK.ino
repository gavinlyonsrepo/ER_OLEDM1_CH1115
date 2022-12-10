
// Example file name : ER_OLEDM1_CH1115_CLOCK.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing  example of a clock and vertical multibuffer mode. just a simple demo,
// sharing multibuffers of same size reduces program memory size.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file for which buffer to use with which test
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// ******************************

#include "ER_OLEDM1_CH1115.hpp"

#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. user adjust

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
ERMCH1115  myOLED(DC, RES, CS);

// ************ Buffer section *****************
// Define a half  screen buffer
uint8_t  halfScreenBuffer[(MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)) / 2]; // half screen buffer 512 bytes


// ********* BITMAP SECTION **********
const PROGMEM uint8_t Signal816[16]  = //mobile signal 16x8px
{
  0x03, 0x05, 0x09, 0xff, 0x09, 0x05, 0xf3, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0xfe, 0x00, 0xff, 0x00
};

const PROGMEM uint8_t Msg816[16]  =  //message   // 'msg', 16x8px
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

// ********* BITMAP SECTION OVER **********


unsigned long previousMillis = 0;        // will store last time  was updated:
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

  // two buffers
  // ________________________
  // |      Icons buffer         |
  // |______________________|
  // |      Time buffer         |
  // |______________________|
  //
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
  // Declare a struct
  MultiBuffer iconBar;

  // Define the struct varibles
  // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&iconBar, halfScreenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT/2, 0, 0);
  myOLED.ActiveBuffer =  &iconBar;   // Set the buffer struct object

  myOLED.OLEDclearBuffer(); // Clear the buffer

  myOLED.setDrawBitmapAddr(true); // for Bitmap Data Vertical  addressed
  myOLED.drawBitmap(4, 0, Signal816, 16, 8, FOREGROUND, BACKGROUND);
  myOLED.drawBitmap(24, 0, Bluetooth88, 8, 8, FOREGROUND, BACKGROUND);
  myOLED.drawBitmap(40, 0, Msg816, 16, 8, FOREGROUND, BACKGROUND);
  myOLED.drawBitmap(64, 0, GPRS88, 8, 8, FOREGROUND, BACKGROUND);
  myOLED.drawBitmap(90, 0, Alarm88, 8, 8, FOREGROUND, BACKGROUND);
  myOLED.drawBitmap(112, 0, Bat816, 16, 8, FOREGROUND, BACKGROUND);
  myOLED.OLEDupdate();
}

void DisplayText()
{
  // Declare a struct
  MultiBuffer textBox;
  // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&textBox, halfScreenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT/2, 0, MYOLEDHEIGHT/2);

  myOLED.ActiveBuffer =  &textBox;   // Set the buffer struct object
  myOLED.OLEDclearBuffer(); // Clear the buffer

  char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  myOLED.setTextColor(FOREGROUND);
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

      myOLED.drawChar(0, 1 ,  value[Hour / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(16, 1 , value[Hour % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(32, 1 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(48, 1 , value[Min / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(66, 1 , value[Min % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(80, 1 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(96, 1 , value[sec / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(112, 1 , value[sec % 10], FOREGROUND, BACKGROUND, 3);

      myOLED.OLEDupdate();
    }
  }
}
