// Example file name : ER_OLEDM1_CH1115_MB_TXTino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of TEXT  mode .
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option MULTI_BUFFER must be selected and only this option.
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// (4) In order to use extended ASCII font (128 -255) ,
//    Mod file UC_FONT_MOD_TWO <ER_OLEDM1_CH1115_font.h> ( and include it just for this test file)
// (5) IN order to use first 30 charcaters of ASCII table 0-30 ,
//    Mod file UC_FONT_MOD_ONE <ER_OLEDM1_CH1115_font.h> (and include it just for this test file)
// ******************************

#include "ER_OLEDM1_CH1115.h"
#include "ER_OLEDM1_CH1115_font.h" // just needed for tests to see font defines status

#define myOLEDheight 64
#define myOLEDwidth  128
#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. user adjust

#define DisplayDelay1 5000 
#define DisplayDelay2 0

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI

ERMCH1115  myOLED(DC, RES, CS); 

// ************* SETUP ***************
void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen
}

// ************** MAIN LOOP ***********
void loop()
{

  // Define a full screen buffer
  uint8_t  textBuffer[(myOLEDwidth * (myOLEDheight / 8)) + 1]; 
  MultiBuffer window;
  window.screenbitmap = (uint8_t*) &textBuffer;

  // Call a function to display text
  DisplayText(&window);

}
// ************** END OF MAIN ***********

// A series of tests to display the text mode
// Test 1 Font size 3 float
// Test 2 font size 2 integer
// Test 3 font size 1 string inverted
// Test 4 draw a single character font size 4
// Test 5 print ASCII  font 0-127
// Test 6 print ASCII font 128-255, commented out as not setup by default, see note 4 at top of file.

void DisplayText(MultiBuffer* targetBuffer)
{

  myOLED.setTextWrap(true);
  myOLED.ActiveBuffer =  targetBuffer;
  myOLED.OLEDclearBuffer(); // Clear the buffer
  while (1)
  {
    // Test 1
    myOLED.setTextColor(FOREGROUND);
    myOLED.setTextSize(3);
    myOLED.setCursor(0, 0);
    myOLED.print(PI);

    // Test 2
    myOLED.setTextSize(2);
    myOLED.setCursor(0, 30);
    int count = 123;
    myOLED.print(count);

    // Test 3
    myOLED.setTextSize(1);
    myOLED.setTextColor(BACKGROUND, FOREGROUND);
    myOLED.setCursor(0, 50);
    myOLED.print(F("Hello World"));

    // Test 4
    myOLED.drawChar(95, 15 , 'H', FOREGROUND, BACKGROUND, 6);

    myOLED.OLEDupdate();  // Write to the buffer
    delay(DisplayDelay1);
    myOLED.OLEDclearBuffer();

    // Test 5
    myOLED.setCursor(0, 0);
    myOLED.setTextColor(FOREGROUND);
    myOLED.setTextSize(1);
    myOLED.print(F("ASCII font "));
    myOLED.setCursor(0, 15);
    char offset = 32;
 #ifdef UC_FONT_MOD_ONE
 offset = 0;
 #endif
    // Print first 127 chars of font
    for (char i = offset; i < 126; i++)
    {
      if (i == '\n' || i == '\r') continue;
      myOLED.print(i);
      delay(DisplayDelay2);
    }
    myOLED.OLEDupdate();  // Write to the buffer
    delay(DisplayDelay1);
    myOLED.OLEDclearBuffer();


 #ifdef UC_FONT_MOD_TWO   
    
    myOLED.setCursor(0, 0);
    myOLED.setTextColor(FOREGROUND);
    myOLED.setTextSize(1);
    myOLED.print(F("ASCII font 128-255"));
    
    uint8_t x = 0;
    uint8_t y = 15;
    myOLED.setCursor(x, y);
    
    for (uint8_t i = 128; i < 255; i++)
    {
      if (x > 180)
      {
        x = 0;
        y += 9;
      }
      myOLED.drawChar(x, y , i, FOREGROUND, BACKGROUND, 1);
      x += 7;
      delay(DisplayDelay2);
    }
    
    myOLED.OLEDupdate();  // Write to the buffer
    delay(DisplayDelay1);
    myOLED.OLEDclearBuffer();
#endif 
  } // while

} // end
