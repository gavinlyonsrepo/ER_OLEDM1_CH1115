// Example file name : ER_OLEDM1_CH1115_MB_TXTino
// Description:
// Test file for ER_OLEDM1_CH1115 library,
// (1) showing use of TEXT  mode .
// (2) showing use of graphic functions from included graphics library.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NB **** NOTES **** NB :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option MULTI_BUFFER must be selected and only this option.
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// (4) Test 6: In order to use extended ASCII font (128 -255) ,
//    Mod file UC_FONT_MOD_TWO <ER_OLEDM1_CH1115_font.h> ( and include it just for this test file)
// (5) For font test 1-6 , default font one is required, for Test 7-13 All other fonts are required
// If non-default fonts are not enabled in font file nothing will appear during these tests.
// ******************************


/*
   Test list
  Text tests. 1-15
  Graphic test. 16
  Misc functions test. 17 A-F

  Test 1 Font size 3 float
  Test 2 font size 2 integer
  Test 3 font size 1 string inverted
  Test 4 draw a single character font size 4
  Test 5 print ASCII  font 0-127
  Test 6 print ASCII font 128-255, if #define UC_FONT_MOD_TWO comment in will not work
  Test 7 "thick" font 2 (NO LOWERCASE)
  Test 8 "seven seg" font 3
  Test 9 "wide" font 4 (NO LOWERCASE)
  Test 10 "tiny" font 5 
  Test 11 "homespun font 6" 
  
  Test 12 "bigNums" font 7 (Numbers ONLY + : ) 
  Test 13 "medNums" font 8 (Numbers ONLY + : ) 

  Test 14 print function DEC HEX test 
  Test 15 Draw text funcion 
  
  Test 16 Graphics 

  Test 17A OLED enable and disable
  Test 17B inverse
  Test 17C OLED flip
  Test 17D contrast
  Test 17E OLED scroll
  Test 17F fade ~ breath effect

*/

#include "ER_OLEDM1_CH1115.hpp"

#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
#define OLEDcontrast 0x80 // Contrast 00 to FF , 0x80 is default. user adjust

#define DisplayDelay5 5000
#define DisplayDelay2 2000
#define DisplayDelay1 1000
#define DisplayDelay0 0

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
  myOLED.OLEDFillScreen(0x0F, 0); // Splash  screen
  delay(DisplayDelay1);
  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
  myOLED.setFontNum(OLEDFontType_Default);
}

// ************** MAIN LOOP ***********
void loop()
{
  // Define a full screen buffer
  uint8_t  textBuffer[(MYOLEDWIDTH * (MYOLEDHEIGHT / 8)) + 1];
  MultiBuffer window;
    // Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
  myOLED.OLEDinitBufferStruct(&window, textBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);

  DisplayText(&window);
  DisplayGraphics(&window);
  DisplayMiscTests(&window);

  myOLED.OLEDPowerDown(); // Turn off DISPLAY when tests over
  while (1) {
    delay(100); // Wait for ever
  }
}
// ************** END OF MAIN ***********

// Text tests , A series of tests to display the text mode
void DisplayText(MultiBuffer* targetBuffer)
{

  myOLED.setTextWrap(true);
  myOLED.ActiveBuffer =  targetBuffer;
  myOLED.OLEDclearBuffer(); // Clear the buffer

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

  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 5
  myOLED.setCursor(0, 0);
  myOLED.setTextColor(FOREGROUND);
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
    delay(DisplayDelay0);
  }

  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();
  
  // Test 7
  myOLED.setFontNum(OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Thick Font:");
  myOLED.setFontNum( OLEDFontType_Thick );
  myOLED.setCursor(0, 15);
  myOLED.print("1234567890123456");
  myOLED.drawChar(70, 25 , 'H', FOREGROUND, BACKGROUND, 4);
  myOLED.setCursor(0, 45);
  myOLED.setTextSize(2);
  myOLED.print("TEST");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 8
  myOLED.setFontNum(OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("7 seg Font:");
  myOLED.setFontNum(OLEDFontType_SevenSeg);
  myOLED.setCursor(0, 15);
  myOLED.print("1234567890abcDEF780xyz45");
  myOLED.setCursor(0, 30);
  myOLED.setTextSize(4);
  myOLED.print("14:30");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 9
  myOLED.setFontNum(OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Wide Font:");
  myOLED.setFontNum(OLEDFontType_Wide);
  myOLED.setCursor(0, 15);
  myOLED.print("123456 XYZABC");
  myOLED.setCursor(0, 35);
  myOLED.setTextSize(2);
  myOLED.print("T 13:57");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 10 tiny
  myOLED.setFontNum(OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("tiny Font:");
  myOLED.setFontNum(OLEDFontType_Tiny);
  myOLED.setCursor(0, 15);
  myOLED.print("123456 tiny");
  myOLED.setCursor(0, 35);
  myOLED.setTextSize(2);
  myOLED.print("T 11:52");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 11  homespun
  myOLED.setFontNum(OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("Home Font:");
  myOLED.setFontNum(OLEDFontType_Homespun);
  myOLED.setCursor(0, 15);
  myOLED.print("123456 home");
  myOLED.setCursor(0, 35);
  myOLED.setTextSize(2);
  myOLED.print("T 19:24");
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();


  //Test 12
  myOLED.setFontNum(OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("BigNums Font:");

  // Test 12a drawText
  myOLED.setFontNum(OLEDFontType_Bignum);
  char myString[9] = {'1', '3', ':', '2', '6', ':', '1', '8'};
  myOLED.drawTextNum(0, 32, myString , BACKGROUND, FOREGROUND); 
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 12b  drawCharNum
  myOLED.drawCharNum(0, 0, '8', FOREGROUND, BACKGROUND); 
  myOLED.drawCharNum(40, 32, '4', BACKGROUND, FOREGROUND);
  myOLED.OLEDupdate();  
  delay(DisplayDelay2);
  myOLED.OLEDclearBuffer();
  
  // Test 12c using print with bigNums font
  myOLED.setTextColor(FOREGROUND, BACKGROUND);
  myOLED.setCursor(0, 0);
  myOLED.print(314);
  myOLED.setCursor(0, 32);
  myOLED.print(19.87);
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 13 mednum font
  myOLED.setFontNum(OLEDFontType_Default );
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print("MedNums Font:");
  
  myOLED.setFontNum(OLEDFontType_Mednum);
  char myString1[9] = {'1', '2', ':', '1', '3', ':', '2', '9'};
  myOLED.drawTextNum(0, 16, myString1 , BACKGROUND, FOREGROUND); // Test 10a drawTextNum
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();

  // Test 13b 
  myOLED.drawCharNum(0, 0, '9', FOREGROUND, BACKGROUND); // Test 10b drawCharNum
  myOLED.drawCharNum(40, 16, '2', BACKGROUND, FOREGROUND);
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
    myOLED.setFontNum(OLEDFontType_Default);
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
  
  myOLED.setFontNum(OLEDFontType_Tiny);
  myOLED.drawText(0,0, myString, FOREGROUND, BACKGROUND,1);
  myOLED.setFontNum(OLEDFontType_Wide);
  myOLED.drawText(0,32, myString1, FOREGROUND, BACKGROUND,2);
  myOLED.OLEDupdate();  
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();
  

} // end

// Function to display Graphics. Test 16
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
  myOLED.OLEDclearBuffer();
  myOLED.OLEDupdate();
}

// Functions tests  Test 17
void DisplayMiscTests(MultiBuffer* targetBuffer)
{
  myOLED.setFontNum(OLEDFontType_Default);
  myOLED.setTextSize(1);
  myOLED.ActiveBuffer =  targetBuffer;

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
