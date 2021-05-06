
// Example file name : ER_OLEDM1_CH1115_BITMAP.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing how to display bitmaps.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see extras folde at URL

// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, setting will change depending on which method you use,
//test 2 3 & 4 are commented out currently, see  USER OPTION SELECTION below.
// test (1) OLED bitmap method, ANY setting on , buffer must BE in PROGMEM
// test (2) OLED buffer method , MULTI_BUFFER or SINGLE_BUFFER setting on , buffer must NOT be in PROGMEM
// test (3)  multibuffer method , MULTI_BUFFER setting on.  buffer must NOT be in PROGMEM
// test (4) singlebuffer method, SINGLE_BUFFER  setting on. buffer must NOT be in PROGMEM

// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// ******************************

#include "ER_OLEDM1_CH1115.h"

#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. user adjust
#define myOLEDheight 64
#define myOLEDwidth  128

// **************** USER OPTION SELECTION ***************
//pick a test to run ONE test and one TEST only
#define test1
//#define test2
//#define test3
//#define test4
//*******************************************************

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI

ERMCH1115  myOLED(DC, RES, CS); //  object , DC, RES, CS

// 'myimage', 128x64px "g lyons" + shapes , SW used to make https://javl.github.io/image2cpp/ vertical addressing
// OG image at project URL, used in test file to test image function can be removed/modded in an actual program

//const uint8_t fullscreenBitmap[] = {
const uint8_t PROGMEM fullscreenBitmap[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x20, 0x20, 0x20, 0x20, 0x60,
  0x40, 0xc0, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xe0, 0xe0, 0xe0, 0x20, 0x20, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xf8, 0xfe, 0xff, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x60, 0xe1, 0xe7, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x38, 0xf8, 0xf8, 0xc8, 0x00, 0x00,
  0x00, 0x00, 0xc8, 0x78, 0x08, 0x00, 0x00, 0xc0, 0xe0, 0x70, 0x10, 0x08, 0x08, 0x08, 0x08, 0x18,
  0x70, 0xe0, 0xc0, 0x00, 0x00, 0x10, 0xf0, 0xf8, 0xf8, 0x20, 0x10, 0x18, 0x18, 0x38, 0xf8, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0xf0, 0xd8, 0x88, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x3e, 0x70, 0x60, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80,
  0xc0, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3e, 0xf8,
  0x70, 0x0e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7e, 0x60, 0xc0, 0x80, 0x80, 0x80, 0xc0,
  0x60, 0x3f, 0x1f, 0x02, 0x00, 0x80, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff,
  0x80, 0x00, 0x00, 0x00, 0xe1, 0x83, 0x83, 0x87, 0x86, 0x8e, 0x7c, 0x38, 0x00, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x38, 0x30, 0x18, 0x06, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0x06, 0x06, 0x06,
  0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6,
  0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6,
  0xf6, 0xf6, 0xf6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07,
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x1f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
  0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
  0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
  0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1f, 0x1f, 0x1f, 0x1f, 0x00
};

// 'small image', 20x20px
uint8_t smallImage  [] = {
  0xff, 0x3f, 0x0f, 0x07, 0x03, 0x13, 0x33, 0x39, 0x39, 0x79, 0xf9, 0xf9, 0xfb, 0xf3, 0xf7, 0xe3,
  0x87, 0x0f, 0x1f, 0xff, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f,
  0x1d, 0x19, 0x10, 0x19, 0x0f, 0x00, 0xc0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x0c, 0x08, 0x08,
  0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f
};


void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0); // Clears screen
  delay(500);
}

void loop()
{
  while (1)
  {
#ifdef test1
    Test1(); // Method (1) OLED bitmap method,Any buffer  setting on, image must BE in PROGMEM
#endif
#ifdef test2
    Test2(); // Method (2) OLED buffer method, MULTI_BUFFER or SINGLE BUFFER setting on, image must NOT BE in PROGMEM
#endif
#ifdef test3
    Test3(); // Method (3) OLED update mutlibuffer mode  , MULTI_BUFFER setting on,  image must not be in PROGMEM
#endif
#ifdef test4
    Test4(); // //Method (4) OLED update  singlebuffer method, SINGLE_BUFFER  setting on, image must not be in PROGMEM
#endif
  }
}

#ifdef test1
void Test1(void)
{
  // Method (1) OLED bitmap method, Any buffer  setting on , image must BE in PROGMEM

  //  x ,y,w,h, bitmap
  myOLED.OLEDBitmap(0, 0 , myOLEDwidth, myOLEDheight, fullscreenBitmap);
  while (1) {
    delay(5000);
  };
}
#endif

#ifdef test2
void Test2(void)
{
  // Method (2) OLED buffer method , MULTI_BUFFER or SINGLE BUFFER setting, on , image must NOT BE in PROGMEM
  const uint8_t bitmapNum = 10; 
  const uint8_t bitmapSize = 20; 
  //  x ,y,w,h, bitmap
  myOLED.OLEDBuffer(30, 10, 20, 20, (uint8_t*)smallImage);
  myOLED.OLEDBuffer(70, 10, 20, 20, (uint8_t*)smallImage);
  for (uint8_t i = 0; i < bitmapNum; i++) 
  {
    myOLED.OLEDBuffer(random(128 - bitmapSize), random(64 - bitmapSize), bitmapSize, bitmapSize, (uint8_t*)smallImage);
    delay(500);
  }
  while (1) {
    delay(5000);
  };

}

#endif

#ifdef test3
void Test3(void)
{
  // Method (3) multibuffer mode  , MULTI_BUFFER setting on, NOTE  buffer must not be in PROGMEM

  MultiBuffer Whole_screen;
  Whole_screen.screenbitmap = (uint8_t*) &fullscreenBitmap;
  Whole_screen.width = myOLEDwidth;
  Whole_screen.height = 64;
  Whole_screen.xoffset = 0; // offset on display
  Whole_screen.yoffset = 0 ;
  myOLED.ActiveBuffer = &Whole_screen;
  myOLED.OLEDupdate();
  while (1) {
    delay(5000);
  };

}
#endif

#ifdef test4
void Test4(void)
{
  //Method (4) singlebuffer method, SINGLE_BUFFER  setting on, NOTE  buffer must not be in PROGMEM

  myOLED.buffer = (uint8_t*) &fullscreenBitmap;
  myOLED.OLEDupdate();
  while (1) {
    delay(5000);
  };
}

#endif