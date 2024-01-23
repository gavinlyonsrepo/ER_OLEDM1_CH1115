 /*!
	@file ER_OLEDM1_CH1115_GRAPHICS.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use 
		graphic functions

	@author Gavin Lyons
	@note
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-# This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.

	 @test
		-# Test 201 Graphics 

*/

#include "ER_OLEDM1_CH1115.hpp"

//Contrast 00 to FF , 0x80 is default. user adjust
#define OLEDcontrast 0x80 

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
// GPIO pin number SCK(UNO 13) , HW SPI , SCK

// Screen setup
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
#define FULLSCREEN (MYOLEDWIDTH  * (MYOLEDHEIGHT / 8))
// Define a Buffer
uint8_t screenBuffer[FULLSCREEN]; 
// instantiate an OLED object
ERMCH1115 myOLED(MYOLEDWIDTH, MYOLEDHEIGHT, DC, RES, CS); 
// instantiate an Shared buffer object , only one in this case to cover whole screen
ERMCH1115_SharedBuffer fullScreen(screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);

//  test timing
#define DisplayDelay5 5000
#define DisplayDelay2 2000
#define DisplayDelay1 1000
#define DisplayDelay0 0

// ************* SETUP ***************
void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x0F, 0); // Splash  screen
  delay(DisplayDelay1);
  myOLED.setTextColor(OLED_WHITE,OLED_BLACK);
  myOLED.setTextSize(1);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.ActiveBufferPtr =  &fullScreen; // Assign Buffer to be the active buffer pointer
  
}

// ************** MAIN LOOP ***********
void loop()
{
  DisplayGraphics();
  myOLED.OLEDPowerDown(); // Turn off DISPLAY when tests over
  while(1){delay(100);};
}
// ************** END OF MAIN ***********


// Function to display Graphics. Test 201
void  DisplayGraphics()
{
  //Q1 ||  Q2
  //---------
  //Q3 ||  Q4
  //
  bool colour = 1;
  uint8_t count = 0;
  myOLED.OLEDclearBuffer(); // Clear the buffer

  while (count < 25)
  {
    colour = !colour;

    //print count 
    myOLED.setCursor(0, 0);
    myOLED.print(count);
    myOLED.setCursor(40, 0);
    myOLED.print(colour);
    // Draw the X
    myOLED.drawLine(64,  0, 64, 64, OLED_WHITE);
    myOLED.drawFastVLine(62, 0, 64, OLED_WHITE);
    myOLED.drawFastHLine(0, 32, 128, OLED_WHITE);

    // Q1
    myOLED.fillRect(0, 10, 20, 20, colour);
    myOLED.fillCircle(40, 20, 10, colour);
    myOLED.drawCircle(40, 20, 10, !colour);
    // Q2
    myOLED.fillTriangle(80, 25, 90, 5, 100, 25, !colour);
    myOLED.drawTriangle(80, 25, 90, 5, 100, 25, colour);
    myOLED.drawRect(105, 10, 15, 15, OLED_WHITE);
    // Q3
    myOLED.fillRoundRect(0, 40, 40, 20, 10, !colour);
    myOLED.drawRoundRect(0, 40, 40, 20, 10, colour);
    // Q4
    char i;
    for (i = 0; i < 10; i ++)
    {
      myOLED.drawRect(70 + i, 40 + i, 50 - i * 2, 20 - i * 2, OLED_WHITE);
      myOLED.OLEDupdate();
      delay(50);
    }
    myOLED.OLEDclearBuffer();
    count++;
  }
  myOLED.OLEDclearBuffer();
  myOLED.OLEDupdate();
}

