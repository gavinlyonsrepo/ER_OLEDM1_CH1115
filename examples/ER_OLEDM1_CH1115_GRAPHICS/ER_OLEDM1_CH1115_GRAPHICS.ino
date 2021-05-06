// Example file name : ER_OLEDM1_CH1115_GRAPHICS.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of graphic functions from included graphics library.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option MULTI_BUFFER must be selected
// and only this option. It is on by default.
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

// ************* SETUP ***************
void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0xE5, 0); // Fill the screen with a a pattern , "just for splashscreen effect"
  delay(1500);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen
}


// *********** MAIN LOOP ******************
void loop()
{

  // Define a full screen buffer
  uint8_t  textBuffer[(myOLEDwidth * (myOLEDheight / 8)) + 1]; // 128 X (64/8) + 1 

  // Declare a struct
  MultiBuffer wholescreen;

  // Define the struct varibles
  wholescreen.screenbitmap = (uint8_t*) &textBuffer;
  wholescreen.width = myOLEDwidth; // bitmap x size, default
  wholescreen.height = myOLEDheight; // bitmap y size, default
  wholescreen.xoffset = 0; // x offset, default
  wholescreen.yoffset = 0; // y offset, default

  DisplayGraphics(&wholescreen);  // Call a function to display graphics pass it the struct

}
// *********** END OF MAIN ***********

// Function to display Graphics.
void  DisplayGraphics(MultiBuffer* targetBuffer)
{
  //Q1 ||  Q2
  //---------
  //Q3 ||  Q4
  //
  bool colour = 1;
  uint8_t count = 0;
  myOLED.ActiveBuffer =  targetBuffer;   // Set the buffer struct object
  myOLED.OLEDclearBuffer(); // Clear the buffer
  while (count < 15)
  {
    colour = !colour;

    // Draw the X
    myOLED.drawLine(64,  0, 64, 64, FOREGROUND);
    myOLED.drawFastVLine(62, 0, 64, FOREGROUND);
    myOLED.drawFastHLine(0, 32, 128, FOREGROUND);

    // Q1
    myOLED.fillRect(0, 10, 20, 20, colour);
    myOLED.fillCircle(40, 20, 10, FOREGROUND);

    // Q2
    myOLED.fillTriangle(80, 25, 90, 5, 100, 25, !colour);
    myOLED.drawRect(105, 10, 15, 15, FOREGROUND);
    // Q3
    myOLED.fillRoundRect(0, 40, 40, 20, 10, !colour);
    // Q4
    char i;
    for (i = 0; i < 10; i ++)
    {
      myOLED.drawRect(70 + i, 40 + i, 50 - i * 2, 20 - i * 2, FOREGROUND);
      myOLED.OLEDupdate();
      delay(50);
    }
    myOLED.OLEDclearBuffer();
    count++;
  }
}

 
