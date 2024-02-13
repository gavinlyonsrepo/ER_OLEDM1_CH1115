 /*!
	@file ER_OLEDM1_CH1115_FUNCTIONS.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use of 
	 various function tests.

	@author Gavin Lyons
	@note
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-# This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.

	 @test
		-# Test 301 OLED enable and disable
		-# Test 302 inverse
		-# Test 303 OLED flip command 180 degree rotate 
		-# Test 304 contrast
		-# Test 305 OLED scroll
		-# Test 306 fade ~ breath effect
		-# Test 307 Rotate Software buffer
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
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.ActiveBufferPtr =  &fullScreen; // Assign Buffer to be the active buffer pointer
  
}

// ************** MAIN LOOP ***********
void loop()
{
  DisplayMiscTests();

  myOLED.OLEDPowerDown(); // Turn off DISPLAY when tests over
  while (1){delay(100);}
}
// ************** END OF MAIN ***********

// Functions tests
void DisplayMiscTests()
{

  //  ** Test 301 OLED enable and disable **
  myOLED.setCursor(0, 30);
  myOLED.print("OLED Disable test 301");
  myOLED.OLEDupdate();

  delay(DisplayDelay2); //display message
  myOLED.OLEDEnable(0); //turn off display (sleep mode 500uA measured)
  delay(DisplayDelay2); //wait for 2
  myOLED.OLEDEnable(1); //turn on
  delay (DisplayDelay2); //display message
  myOLED.OLEDclearBuffer();

  // ** Test 302 inverse **
  myOLED.setCursor(0, 10);
  myOLED.print("Inverse test 302");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);
  myOLED.OLEDInvert(1); // Inverted
  delay(DisplayDelay5);
  myOLED.OLEDInvert(0);
  delay(DisplayDelay1);


  // ** Test 303 OLED flip **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  myOLED.print("Flip test 303");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);
  myOLED.OLEDFlip(1);
  delay(DisplayDelay5);
  myOLED.OLEDFlip(0);
  delay(DisplayDelay1);

  // ** Test 304 contrast **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print("Contrast test 304");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);
  myOLED.OLEDFillScreen(0x77, 0); // fill screen

  myOLED.OLEDContrast(0x00);
  delay(DisplayDelay1);
  myOLED.OLEDContrast(0x80);
  delay(DisplayDelay1);
  myOLED.OLEDContrast(0xFF);
  delay(DisplayDelay1);
  myOLED.OLEDContrast(OLEDcontrast);
  delay(DisplayDelay1);
  myOLED.OLEDclearBuffer();


  // ** Test 305 OLED scroll **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 40);
  myOLED.print("Scroll test 305");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);

  // See .cpp file for more info on these parmeters.
  uint8_t timeInterval = 0x00; // 6 frames 0x00 - 0x07
  uint8_t scrollDirection = 0x26; //right 0x26 or 0x27
  uint8_t scrollMode = 0x28; // contiunous 0x28-0x2A,
  myOLED.OLEDscrollSetup(timeInterval, scrollDirection , scrollMode);
  myOLED.OLEDscroll(1); //start scroll
  delay(15000);
  myOLED.OLEDscroll(0); // stop Scroll

  delay(1);

  timeInterval = 0x02; // 64 frames , 0x00 - 0x07
  scrollDirection = 0x27; // left , 0x26 or 0x27
  scrollMode = 0x29; // contiunous 0x28 one shot 0x29 , one col 0x2A,
  myOLED.OLEDscrollSetup(timeInterval, scrollDirection , scrollMode);
  myOLED.OLEDscroll(1); //start
  delay(15000);
  myOLED.OLEDscroll(0); // stop

  // ** TEST 306 fade ~ breath effect **
  myOLED.OLEDclearBuffer();
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  myOLED.print("Fade effect test 306");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);
  myOLED.OLEDfadeEffect();
  myOLED.OLEDFillScreen(0xE3, 0);
  delay(10000);
  myOLED.OLEDfadeEffect(0x00); // switch off fade

  // ** TEST 307 rotate software Buffer **
  
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 30);
  myOLED.println("rotate Buffer");
  myOLED.print("test 307");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);
  myOLED.OLEDclearBuffer();

  
  myOLED.setRotation(CH1115_Degrees_0);
  myOLED.setCursor(5, 5);
  myOLED.print("rotate 0");
  myOLED.setCursor(5, 50);
  myOLED.print("bottom       !");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  myOLED.setRotation(CH1115_Degrees_90);
  myOLED.setCursor(5, 5);
  myOLED.print("rotate 90");
  myOLED.setCursor(5, 110);
  myOLED.print("bottom  !");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  myOLED.setRotation(CH1115_Degrees_180);
  myOLED.setCursor(5, 5);
  myOLED.print("rotate 180");
  myOLED.setCursor(5, 50);
  myOLED.print("bottom       !");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  myOLED.setRotation(CH1115_Degrees_270);
  myOLED.setCursor(5, 5);
  myOLED.print("rotate    270");
  myOLED.setCursor(5, 110);
  myOLED.print("bottom  !");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);

  myOLED.setRotation(CH1115_Degrees_0); //back to normal rotation
  myOLED.OLEDclearBuffer();

  myOLED.OLEDclearBuffer();
  myOLED.setCursor(15, 25);
  myOLED.print("End of tests!");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);

}

// ************** EOF **************
