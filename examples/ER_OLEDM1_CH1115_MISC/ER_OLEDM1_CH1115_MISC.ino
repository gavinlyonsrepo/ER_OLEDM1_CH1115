 /*!
	@file ER_OLEDM1_CH1115_MISC.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use of Text,
		graphic methods, and various function tests.

	@author Gavin Lyons
	@note
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-# This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
		-# Test 6: In order to use extended ASCII font (128 -255) , Mod file UC_FONT_MOD_TWO <ER_OLEDM1_CH1115_font.h> ( and include it just for this test file)
		-# For font test 1-6 , default font one is required, for Test 7-13 All other fonts are required
			If non-default fonts are not enabled in font file NOTHING will appear on OLED during these tests.

	 @test
		-# Test 1 Font size 3 float
		-# Test 2 font size 2 integer
		-# Test 3 font size 1 string inverted
		-# Test 4 draw a single character font size 4
		-# Test 5 print ASCII  font 0-127
		-# Test 6 print ASCII font 128-255, if  UC_FONT_MOD_TWO comment in will not work
		-# Test 7 "thick" font 2 (NO LOWERCASE)
		-# Test 8 "seven seg" font 3
		-# Test 9 "wide" font 4 (NO LOWERCASE)
		-# Test 10 "tiny" font 5 
		-# Test 11 "homespun font 6" 
		-# Test 12 "bigNums" font 7 (Numbers ONLY + : ) 
		-# Test 13 "medNums" font 8 (Numbers ONLY + : ) 
		-# Test 14 print function DEC HEX test 
		-# Test 15 Draw text funcion 
		-# Test 16 Graphics 
		-# Test 17A OLED enable and disable
		-# Test 17B inverse
		-# Test 17C OLED flip
		-# Test 17D contrast
		-# Test 17E OLED scroll
		-# Test 17F fade ~ breath effect
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

// Buffer setup
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
// Define a Buffer
uint8_t  screenBuffer[MYOLEDWIDTH  * (MYOLEDHEIGHT / 8)]; 
// instantiate an OLED object
ERMCH1115  myOLED(DC, RES, CS); 
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
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
  myOLED.ActiveBufferPtr =  &fullScreen; // Assign Buffer to be the active buffer pointer
  
}

// ************** MAIN LOOP ***********
void loop()
{
  DisplayText();
  DisplayGraphics();
  DisplayMiscTests();

  myOLED.OLEDPowerDown(); // Turn off DISPLAY when tests over
  while (1) {
    delay(100); // Wait for ever
  }
}
// ************** END OF MAIN ***********

// Text tests , A series of tests to display the text mode
void DisplayText()
{
  myOLED.setTextWrap(true);
  myOLED.OLEDclearBuffer(); // Clear the buffer

  // Test 1
  myOLED.setTextColor(OLED_WHITE);
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
  myOLED.setTextColor(OLED_BLACK, OLED_WHITE);
  myOLED.setCursor(0, 50);
  myOLED.print(F("Hello World"));

  // Test 4
  myOLED.drawChar(95, 15 , 'H', OLED_WHITE, OLED_BLACK, 6);

  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 5
  myOLED.setCursor(0, 0);
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);
  myOLED.print(F("ASCII font "));
  myOLED.setCursor(0, 15);

  // Print first 127 chars of font
  for (char i = 0; i < 126; i++)
  {
    if (i == '\n' || i == '\r') continue;
    myOLED.print(i);
    delay(DisplayDelay0);
  }
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  myOLED.setCursor(0, 0);
  myOLED.setTextColor(OLED_WHITE);
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
    myOLED.drawChar(x, y , i, OLED_WHITE, OLED_BLACK, 1);
    x += 7;
    delay(DisplayDelay0);
  }

  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();
  
  // Test 7
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Thick Font:");
  myOLED.setFontNum(myOLED.OLEDFontType_Thick );
  myOLED.setCursor(0, 15);
  myOLED.print("1234567890123456");
  myOLED.drawChar(70, 25 , 'H', OLED_WHITE, OLED_BLACK, 4);
  myOLED.setCursor(0, 45);
  myOLED.setTextSize(2);
  myOLED.print("TEST");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 8
  myOLED.setFontNum(myOLED.OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("7 seg Font:");
  myOLED.setFontNum(myOLED.OLEDFontType_SevenSeg);
  myOLED.setCursor(0, 15);
  myOLED.print("1234567890abcDEF780xyz45");
  myOLED.setCursor(0, 30);
  myOLED.setTextSize(4);
  myOLED.print("14:30");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 9
  myOLED.setFontNum(myOLED.OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Wide Font:");
  myOLED.setFontNum(myOLED.OLEDFontType_Wide);
  myOLED.setCursor(0, 15);
  myOLED.print("123456 XYZABC");
  myOLED.setCursor(0, 35);
  myOLED.setTextSize(2);
  myOLED.print("T 13:57");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 10 tiny
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("tiny Font:");
  myOLED.setFontNum(myOLED.OLEDFontType_Tiny);
  myOLED.setCursor(0, 15);
  myOLED.print("123456 tiny");
  myOLED.setCursor(0, 35);
  myOLED.setTextSize(2);
  myOLED.print("T 11:52");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 11  homespun
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Home Font:");
  myOLED.setFontNum(myOLED.OLEDFontType_Homespun);
  myOLED.setCursor(0, 15);
  myOLED.print("123456 home");
  myOLED.setCursor(0, 35);
  myOLED.setTextSize(2);
  myOLED.print("T 19:24");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();


  //Test 12
  myOLED.setFontNum(myOLED.OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("BigNums Font:");

  // Test 12a drawText
  myOLED.setFontNum(myOLED.OLEDFontType_Bignum);
  char myString[9] = {'1', '3', ':', '2', '6', ':', '1', '8'};
  myOLED.drawTextNum(0, 32, myString , OLED_BLACK, OLED_WHITE); 
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 12b  drawCharNum
  myOLED.drawCharNum(0, 0, '8', OLED_WHITE, OLED_BLACK); 
  myOLED.drawCharNum(40, 32, '4', OLED_BLACK, OLED_WHITE);
  myOLED.OLEDupdate();  
  delay(DisplayDelay2);
  myOLED.OLEDclearBuffer();
  
  // Test 12c using print with bigNums font
  myOLED.setTextColor(OLED_WHITE, OLED_BLACK);
  myOLED.setCursor(0, 0);
  myOLED.print(314);
  myOLED.setCursor(0, 32);
  myOLED.print(19.87);
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 13 mednum font
  myOLED.setFontNum(myOLED.OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("MedNums Font:");
  
  myOLED.setFontNum(myOLED.OLEDFontType_Mednum);
  char myString1[9] = {'1', '2', ':', '1', '3', ':', '2', '9'};
  myOLED.drawTextNum(0, 16, myString1 , OLED_BLACK, OLED_WHITE); // Test 10a drawTextNum
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 13b 
  myOLED.drawCharNum(0, 0, '9', OLED_WHITE, OLED_BLACK); // Test 10b drawCharNum
  myOLED.drawCharNum(40, 16, '2', OLED_BLACK, OLED_WHITE);
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 13c using print with medNums font
  myOLED.setCursor(0, 0);
  myOLED.print(317);
  myOLED.setCursor(0, 16);
  myOLED.print(19.288 , 2); // print 19.29
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 14 print function
    myOLED.setFontNum(myOLED.OLEDFontType_Default);
    myOLED.setCursor(0, 0);
    myOLED.print(47 , DEC);
    myOLED.setCursor(0, 16);
    myOLED.print(47 , HEX); 
    myOLED.setCursor(0, 32);
    myOLED.print(47, BIN);
    myOLED.setCursor(0, 48);
    myOLED.print(47 , OCT);
    myOLED.OLEDupdate();  
    delay(DisplayDelay5);
    myOLED.OLEDclearBuffer();

  // Test 15 Drawtext funtion. buignum func not going work over size. 
  
  myOLED.setFontNum(myOLED.OLEDFontType_Tiny);
  myOLED.drawText(0,0, myString, OLED_WHITE, OLED_BLACK,1);
  myOLED.setFontNum(myOLED.OLEDFontType_Wide);
  myOLED.drawText(0,32, myString1, OLED_WHITE, OLED_BLACK,2);
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();
  

} // end

// Function to display Graphics. Test 16
void  DisplayGraphics()
{
  //Q1 ||  Q2
  //---------
  //Q3 ||  Q4
  //
  bool colour = 1;
  uint8_t count = 0;
  myOLED.OLEDclearBuffer(); // Clear the buffer
  while (count < 15)
  {
    colour = !colour;

    // Draw the X
    myOLED.drawLine(64,  0, 64, 64, OLED_WHITE);
    myOLED.drawFastVLine(62, 0, 64, OLED_WHITE);
    myOLED.drawFastHLine(0, 32, 128, OLED_WHITE);

    // Q1
    myOLED.fillRect(0, 10, 20, 20, colour);
    myOLED.fillCircle(40, 20, 10, OLED_WHITE);

    // Q2
    myOLED.fillTriangle(80, 25, 90, 5, 100, 25, !colour);
    myOLED.drawRect(105, 10, 15, 15, OLED_WHITE);
    // Q3
    myOLED.fillRoundRect(0, 40, 40, 20, 10, !colour);
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

// Functions tests  Test 17
void DisplayMiscTests()
{
  myOLED.setFontNum(myOLED.OLEDFontType_Default);
  myOLED.setTextSize(1);

  //  ** Test A OLED enable and disable **
  myOLED.setCursor(0, 30);
  myOLED.print("OLED Disable test 1");
  myOLED.OLEDupdate();

  delay(DisplayDelay2); //display message
  myOLED.OLEDEnable(0); //turn off display (sleep mode 500uA measured)
  delay(DisplayDelay2); //wait for 2
  myOLED.OLEDEnable(1); //turn on
  delay (DisplayDelay2); //display message
  myOLED.OLEDclearBuffer();

  // ** Test B inverse **
  myOLED.setCursor(0, 10);
  myOLED.print("OLED Inverse test 2");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);
  myOLED.OLEDInvert(1); // Inverted
  delay(DisplayDelay5);
  myOLED.OLEDInvert(0);
  delay(DisplayDelay1);


  // ** Test C OLED flip **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  myOLED.print("Flip test 3");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);
  myOLED.OLEDFlip(1);
  delay(DisplayDelay5);
  myOLED.OLEDFlip(0);
  delay(DisplayDelay1);

  // ** Test D contrast **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print("Contrast test 4");
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


  // ** Test E OLED scroll **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 40);
  myOLED.print("Scroll test 5 ");
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

  // ** TEST F fade ~ breath effect **
  myOLED.OLEDclearBuffer();
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  myOLED.print("Fade effect test 6");
  myOLED.OLEDupdate();
  delay(DisplayDelay2);
  myOLED.OLEDfadeEffect();
  myOLED.OLEDFillScreen(0xE3, 0);
  delay(10000);
  myOLED.OLEDfadeEffect(0x00); // switch off fade

  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);

  myOLED.print("End of tests");
  myOLED.OLEDupdate();
  delay(DisplayDelay5);

}

// ************** EOF **************
