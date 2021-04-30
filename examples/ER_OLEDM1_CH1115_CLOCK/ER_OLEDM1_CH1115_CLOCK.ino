
// Example file name : ER_OLEDM1_CH1115_CLOCK.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use an example of a clock . just a simple demo.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file for which buffer to use with which test
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// ******************************

#include "ER_OLEDM1_CH1115.h"

#define myOLEDheight 64
#define myOLEDwidth  128
#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. user adjust

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
ERMCH1115  myOLED(DC, RES, CS); 

// **************** USER OPTION SELECTION ***************
//pick a test to run ONE test and one TEST only, and select relevant buffer mode.
#define test0 // multibuffer mode, 7 buffers
//#define test1 //multibuffer mode, two buffer
//#define test2 // mulitbuffer mode, one buffers
//#define test3 // single buffer mode, fullscreen
//*******************************************************

// ********* BITMAP SECTION **********
const uint8_t Signal816[16]  = //mobie signal
{
  0x03, 0x05, 0x09, 0xff, 0x09, 0x05, 0xf3, 0x00, 0xf8, 0x00, 0xfc, 0x00, 0xfe, 0x00, 0xff, 0x00
};

const uint8_t Msg816[16]  =  //message
{
  // 'msg', 16x8px
  0x00, 0x00, 0x00, 0xff, 0x85, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x85, 0xff, 0x00, 0x00, 0x00
};

const uint8_t Bat816[16]  = //battery
{
  // 'battery', 16x8px
  0x00, 0x00, 0x7e, 0x42, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xbd, 0xbd, 0x81, 0xff, 0x00
};

const uint8_t Bluetooth88[8]  = // bluetooth
{
  // 'bluetooth', 8x8px
  0x00, 0x42, 0x24, 0xff, 0x99, 0x5a, 0x24, 0x00
};

const uint8_t GPRS88[8]  = //GPRS
{ // 'gps', 8x8px
  0xc3, 0x81, 0x3c, 0x42, 0x52, 0x34, 0x81, 0xc3
};

const uint8_t Alarm88[8] = //alram
{
  // 'alarm', 8x8px
  0x83, 0xbd, 0x42, 0x4a, 0x52, 0x52, 0xbd, 0x83
};
// ********* BITMAP SECTION OVER **********


unsigned long previousMillis = 0;        // will store last time  was updated:
const long interval = 1000;           // interval  (milliseconds)
int count = 50;

// ************* SETUP ***************
void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0xE5, 0); // Fill the screen with a a pattern , just for splashscreen effect
  delay(1500);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen
}


// *********** MAIN LOOP ******************

void loop()
{

#ifdef test0
  //
  // Seven buffers, x for bitmaps
  // ________________________
  // | X |X | X | X | X | X |
  // |----------------------|
  // |      Text area       |
  // |______________________|
  //
  DisplayTopBar();
  while (1)
  {
    DisplayText();
  }

#endif //test0

#ifdef test1

  // two buffers
  // ________________________
  // |      Icons area      |
  // |----------------------|
  // |      Text area       |
  // |______________________|
  //
  DisplayTopBar();
  while (1)
  {
    DisplayText();
  }

#endif //test1

#ifdef test2
  // Define a full screen buffer
  uint8_t  textBuffer[(myOLEDwidth * ((myOLEDheight - 8) / 8)) + 1]; //1024-128;

  // Declare a struct
  MultiBuffer TextBox;

  // Define the struct varibles
  TextBox.screenbitmap = (uint8_t*) &textBuffer;
  TextBox.width = myOLEDwidth; // bitmap x size, default
  TextBox.height = myOLEDheight - 8; // bitmap y size, default
  TextBox.xoffset = 0; // x offset, default
  TextBox.yoffset = 8; // y offset, default
  DisplayClock(&TextBox);

#endif //test2

#ifdef  test3
  //  Single  buffer in single buffer mode
  DisplayText();
#endif //test3

}
// *********** END OF MAIN ***********

#ifdef test0
void DisplayTopBar()
{
  // Declare the structs
  MultiBuffer SignalBar;
  MultiBuffer Bluetooth;
  MultiBuffer Msg;
  MultiBuffer GPRSS;
  MultiBuffer Alarm;
  MultiBuffer Bat;

  // Define the struct varibles
  SignalBar.screenbitmap = (uint8_t*) &Signal816;
  SignalBar.width = 16; // bitmap x size,
  SignalBar.height = 8; // bitmap y size,
  SignalBar.xoffset = 0; // x offset,
  SignalBar.yoffset = 0; // y offset,

  Bluetooth.screenbitmap = (uint8_t*) &Bluetooth88;
  Bluetooth.width = 8; // bitmap x size,
  Bluetooth.height = 8; // bitmap y size,
  Bluetooth.xoffset = 20; // x offset,
  Bluetooth.yoffset = 0; // y offset,

  Msg.screenbitmap = (uint8_t*) &Msg816;
  Msg.width = 16; // bitmap x size,
  Msg.height = 8; // bitmap y size,
  Msg.xoffset = 40; // x offset,
  Msg.yoffset = 0; // y offset,

  GPRSS.screenbitmap = (uint8_t*) &GPRS88;
  GPRSS.width = 8; // bitmap x size,
  GPRSS.height = 8; // bitmap y size,
  GPRSS.xoffset = 60; // x offset,
  GPRSS.yoffset = 0; // y offset,

  Alarm.screenbitmap = (uint8_t*) &Alarm88;
  Alarm.width = 8; // bitmap x size,
  Alarm.height = 8; // bitmap y size,
  Alarm.xoffset = 80; // x offset,
  Alarm.yoffset = 0; // y offset,

  Bat.screenbitmap = (uint8_t*) &Bat816;
  Bat.width = 16; // bitmap x size,
  Bat.height = 8; // bitmap y size,
  Bat.xoffset = 110; // x offset,
  Bat.yoffset = 0; // y offset,

  myOLED.ActiveBuffer =  &Bluetooth;   // Set the buffer struct object
  myOLED.OLEDupdate();
  myOLED.ActiveBuffer =  &SignalBar;   // Set the buffer struct object
  myOLED.OLEDupdate();
  myOLED.ActiveBuffer =  &Msg;   // Set the buffer struct object
  myOLED.OLEDupdate();
  myOLED.ActiveBuffer =  &GPRSS;   // Set the buffer struct object
  myOLED.OLEDupdate();
  myOLED.ActiveBuffer =  &Alarm;   // Set the buffer struct object
  myOLED.OLEDupdate();
  myOLED.ActiveBuffer =  &Bat;   // Set the buffer struct object
  myOLED.OLEDupdate();
}

void DisplayText()
{
  // Define buffer
  uint8_t  textBuffer[896 + 1];
  // Declare a struct
  MultiBuffer textBox;

  // Define the struct varibles
  textBox.screenbitmap = (uint8_t*) &textBuffer;
  textBox.width = myOLEDwidth; // bitmap x size, default
  textBox.height = 56; // bitmap y size, default
  textBox.xoffset = 0; // x offset, default
  textBox.yoffset = 9; // y offset, default

  myOLED.ActiveBuffer =  &textBox;   // Set the buffer struct object
  myOLED.OLEDclearBuffer(); // Clear the buffer

  char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setCursor(30, 46);
  myOLED.print(F("Gavin Lyons"));

  uint8_t sec = 0;
  uint8_t Hour = 12;
  uint8_t Min = 35;
  uint8_t Sec = 55;

  while (1)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      sec++;
      Sec = sec;
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
            Sec = 0;
          }
        }
      }

      myOLED.drawChar(0, 16 ,  value[Hour / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(16, 16 , value[Hour % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(32, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(48, 16 , value[Min / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(66, 16 , value[Min % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(80, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(96, 16 , value[Sec / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(112, 16 , value[Sec % 10], FOREGROUND, BACKGROUND, 3);

      myOLED.OLEDupdate();
    }
  }
}

#endif // test0


#ifdef test1
void DisplayTopBar()
{
  // Define a top bar screen buffer
  uint8_t  topBarBuffer[myOLEDwidth + 1]; // 129

  // Declare a struct
  MultiBuffer topBar;

  // Define the struct varibles
  topBar.screenbitmap = (uint8_t*) &topBarBuffer;
  topBar.width = 128; // bitmap x size, default
  topBar.height = 8; // bitmap y size, default
  topBar.xoffset = 0; // x offset, default
  topBar.yoffset = 0; // y offset, default
  myOLED.ActiveBuffer =  &topBar;   // Set the buffer struct object

  myOLED.OLEDclearBuffer(); // Clear the buf
  myOLED.OLEDBuffer(4, 2 , 16, 8, (uint8_t*)Signal816);
  myOLED.OLEDBuffer(24, 2 , 8, 8, (uint8_t*)Bluetooth88);
  myOLED.OLEDBuffer(40, 2 , 16, 8, (uint8_t*)Msg816);
  myOLED.OLEDBuffer(64, 2 , 8, 8, (uint8_t*)GPRS88);
  myOLED.OLEDBuffer(90, 2 , 8, 8, (uint8_t*)Alarm88);
  myOLED.OLEDBuffer(112, 2 , 16, 8, (uint8_t*)Bat816);
}

void DisplayText()
{
  // Define buffer
  uint8_t  textBuffer[896 + 1];
  // Declare a struct
  MultiBuffer textBox;

  // Define the struct varibles
  textBox.screenbitmap = (uint8_t*) &textBuffer;
  textBox.width = myOLEDwidth; // bitmap x size, default
  textBox.height = 56; // bitmap y size, default
  textBox.xoffset = 0; // x offset, default
  textBox.yoffset = 9; // y offset, default

  myOLED.ActiveBuffer =  &textBox;   // Set the buffer struct object
  myOLED.OLEDclearBuffer(); // Clear the buffer

  char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setCursor(30, 46);
  myOLED.print(F("Gavin Lyons"));

  uint8_t sec = 0;
  uint8_t Hour = 12;
  uint8_t Min = 35;
  uint8_t Sec = 55;

  while (1)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      sec++;
      Sec = sec;
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
            Sec = 0;
          }
        }
      }

      myOLED.drawChar(0, 16 ,  value[Hour / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(16, 16 , value[Hour % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(32, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(48, 16 , value[Min / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(66, 16 , value[Min % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(80, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(96, 16 , value[Sec / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(112, 16 , value[Sec % 10], FOREGROUND, BACKGROUND, 3);

      myOLED.OLEDupdate();
    }
  }
}

#endif // test1


#ifdef test2
void  DisplayClock(MultiBuffer* targetBuffer)
{

  myOLED.ActiveBuffer =  targetBuffer;   // Set the buffer struct object
  myOLED.OLEDclearBuffer(); // Clear the buffer

  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setCursor(30, 46);
  myOLED.print(F("Gavin Lyons"));
  myOLED.OLEDBuffer(4, 2 , 16, 8, (uint8_t*)Signal816);
  myOLED.OLEDBuffer(24, 2 , 8, 8, (uint8_t*)Bluetooth88);
  myOLED.OLEDBuffer(40, 2 , 16, 8, (uint8_t*)Msg816);
  myOLED.OLEDBuffer(64, 2 , 8, 8, (uint8_t*)GPRS88);
  myOLED.OLEDBuffer(90, 2 , 8, 8, (uint8_t*)Alarm88);
  myOLED.OLEDBuffer(112, 2 , 16, 8, (uint8_t*)Bat816);

  char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  uint8_t sec = 0;
  uint8_t Hour = 12;
  uint8_t Min = 35;
  uint8_t Sec = 55;

  while (1)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      sec++;
      Sec = sec;
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
            Sec = 0;
          }
        }
      }
      myOLED.drawChar(0, 16 ,  value[Hour / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(16, 16 , value[Hour % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(32, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(48, 16 , value[Min / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(66, 16 , value[Min % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(80, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(96, 16 , value[Sec / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(112, 16 , value[Sec % 10], FOREGROUND, BACKGROUND, 3);

      myOLED.OLEDupdate();
    }
  }
}
#endif //test2

#ifdef test3

void DisplayText()
{
  uint8_t  screenBuffer[1024];
  myOLED.buffer = (uint8_t*) &screenBuffer;  // Assign the pointer to the buffer
  myOLED.OLEDclearBuffer(); // Clear the buffer


  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setCursor(30, 56);
  myOLED.print(F("Gavin Lyons"));
  myOLED.OLEDupdate();

  char value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  uint8_t sec = 0;
  uint8_t Hour = 12;
  uint8_t Min = 35;
  uint8_t Sec = 55;

  while (1)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      sec++;
      Sec = sec;
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
            Sec = 0;
          }
        }
      }
      myOLED.drawChar(0, 16 ,  value[Hour / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(16, 16 , value[Hour % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(32, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(48, 16 , value[Min / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(64, 16 , value[Min % 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(80, 16 , ':', FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(96, 16 , value[Sec / 10], FOREGROUND, BACKGROUND, 3);
      myOLED.drawChar(112, 16 , value[Sec % 10], FOREGROUND, BACKGROUND, 3);

      myOLED.OLEDupdate();
      //Draw bitmap after update as they are not drawn to buffer
      myOLED.OLEDBuffer(4, 2 , 16, 8, (uint8_t*)Signal816);
      myOLED.OLEDBuffer(24, 2 , 8, 8, (uint8_t*)Bluetooth88);
      myOLED.OLEDBuffer(40, 2 , 16, 8, (uint8_t*)Msg816);
      myOLED.OLEDBuffer(64, 2 , 8, 8, (uint8_t*)GPRS88);
      myOLED.OLEDBuffer(90, 2 , 8, 8, (uint8_t*)Alarm88);
      myOLED.OLEDBuffer(112, 2 , 16, 8, (uint8_t*)Bat816);
    }
  }// while
} // function

#endif //test3
