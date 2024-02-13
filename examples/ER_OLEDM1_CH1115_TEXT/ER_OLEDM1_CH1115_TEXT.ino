 /*!
	@file ER_OLEDM1_CH1115_TEXT.ino
	@brief Example file for ER_OLEDM1_CH1115 library, showing use of Text,
		graphic methods, and various function tests.

	@author Gavin Lyons
	@note
		-# GPIO is for arduino UNO for other tested MCU see readme.
		-# This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
		-# If non-default fonts are not enabled in font file NOTHING will appear on OLED during these tests for fonts 2-12

  @test
    -# 1 Test1 font size 3 string
    -# 2 Test2 font size 2 string
    -# 3 Test3 font size 1 string inverted
    -# 4 Test4 draw a single character font size 4, 4B drawtext method
    -# 5 Test5 print ASCII font 0-127
    -# 6 Test6 text wrap print and drawtext
    -# 7 Test7 print function integer
    -# 8 Test8 print function float + numerical types (HEX BIN etc)
    -# 9 Test9 "thick" font 2
    -# 10 Test10 "seven segment" font 3
    -# 11 Test11 "wide " font 4
    -# 12 Test12 "tiny" font 5
    -# 13 Test13 "homespun" font 6
    -# 14 Test14 "bignum" font 7
    -# 15 Test15 "mednums" font 8
    -# 16 Test16 "Arial Round" font 9
    -# 17 Test17 "Arial bold" font 10
    -# 18 Test18 "Mia" font 11
    -# 19 Test19 "dedica" font 12
    -# 20 Test20 Error checking
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
#define MYCOUNT_UPTIME 150

// ************* SETUP ***************
void setup()
{
  Serial.begin(38400);  // For Test 20 error checking only
  delay(100);
  Serial.println("OLED START!");
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x3F, 0); // Splash  screen
  delay(1000);
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.ActiveBufferPtr =  &fullScreen; // Assign Buffer to be the active buffer pointer
  
}

// ************** MAIN LOOP ***********
void loop()
{
  DisplayText();      // Tests 1-8
  DisplayFonts();     // Tests 9-13
  DisplayFontsTwo();  // Tests 14-19
  // ErrorChecking();    // Test 20
  myOLED.OLEDPowerDown(); // Turn off DISPLAY when tests over
  Serial.println("OLED END!");
  while (1) {delay(100);};
}
// ************** END OF MAIN ***********

void DisplayText() {
  char myString[9] = { '1', '0', ':', '1', '6', ':', '2', '9' };
  myOLED.setFontNum(CH1115Font_Default);

  // Test 1
  myOLED.setTextColor(OLED_WHITE, OLED_BLACK);
  myOLED.setTextSize(3);
  myOLED.setCursor(0, 0);
  myOLED.print(F("Hello"));

  // Test 2
  myOLED.setTextSize(2);
  myOLED.setCursor(0, 30);
  myOLED.print(F("1234567890"));

  // Test 3
  myOLED.setTextSize(1);
  myOLED.setTextColor(OLED_BLACK, OLED_WHITE);
  myOLED.setCursor(0, 50);
  myOLED.print(F("HelloWorld"));

  // Test 4
  myOLED.drawChar(150, 25, 'H', OLED_WHITE, OLED_BLACK, 4);

  TestReset();

  // Test 4b  Drawtext funtion.() bignum func not going work over size)
  myOLED.drawText(0, 0, myString, OLED_WHITE, OLED_BLACK, 1);
  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE, 2);  //inverted

  TestReset();

  // Test 5
  myOLED.setCursor(0, 0);
  myOLED.setTextColor(OLED_WHITE, OLED_BLACK);
  myOLED.setTextSize(1);
  myOLED.print(F("ASCII font 0-127"));
  myOLED.setCursor(0, 15);
  // Print first 127 chars of font
  for (char i = 0; i < 126; i++) {
    if (i == '\n' || i == '\r') continue;
    myOLED.print(i);
    delay(1);
  }
  TestReset();

  // Test 6 testwrap
  // test 6a fonts 1-6
  myOLED.drawText(80, 0, myString, OLED_BLACK, OLED_WHITE, 2);  //inverted
  myOLED.setCursor(80, 32);
  myOLED.setTextSize(2);
  myOLED.print("Text wrap print");
  TestReset();
  // test 6b fonts 7-12
  myOLED.setFontNum(CH1115Font_ArialBold);
  myOLED.drawText(80, 0, myString, OLED_BLACK, OLED_WHITE);  //inverted
  myOLED.setCursor(80, 32);
  myOLED.print("Text wrap");
  TestReset();

  // Test 7
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.setCursor(0, 0);
  myOLED.print(12569);

  // Test 8
  myOLED.setCursor(5, 30);
  myOLED.print(33.91674, 2);  // will print 33.92

  myOLED.setCursor(5, 40);
  myOLED.print(-211);

  TestReset();

  // Test 8b
  myOLED.setCursor(0, 0);
  myOLED.print(47, DEC);
  myOLED.setCursor(0, 16);
  myOLED.print(47, HEX);
  myOLED.setCursor(0, 32);
  myOLED.print(47, BIN);
  myOLED.setCursor(0, 48);
  myOLED.print(47, OCT);

  TestReset();

}  // end function


void DisplayFonts() {

  myOLED.setTextWrap(true);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextColor(OLED_WHITE, OLED_BLACK);
  myOLED.OLEDclearBuffer();  // Clear the buffer

  // Test 9
  myOLED.setCursor(0, 0);
  myOLED.print(F("Thick Font:"));
  myOLED.setFontNum(CH1115Font_Thick);
  myOLED.setCursor(0, 15);
  myOLED.print(F("THICK FONT 82*!"));
  myOLED.drawChar(150, 25, 'T', OLED_WHITE, OLED_BLACK, 4);
  myOLED.setCursor(0, 40);
  myOLED.setTextSize(2);
  myOLED.print(F("TAB 6279"));

  TestReset();

  // Test 10
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Seven Segment  Font:"));
  myOLED.setFontNum(CH1115Font_Seven_Seg);
  myOLED.setCursor(0, 15);
  myOLED.print(F("Seven seg  45638299"));
  myOLED.drawChar(150, 25, 'S', OLED_WHITE, OLED_BLACK, 4);
  myOLED.setCursor(0, 40);
  myOLED.setTextSize(3);
  myOLED.print(F("3941"));


  TestReset();

  // Test 11
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Wide Font:"));
  myOLED.setFontNum(CH1115Font_Wide);
  myOLED.setCursor(0, 15);
  myOLED.print(F("WIDE FONT 38*!"));
  myOLED.drawChar(150, 25, 'W', OLED_WHITE, OLED_BLACK, 3);
  myOLED.setCursor(0, 40);
  myOLED.setTextSize(2);
  myOLED.print(3.14);

  TestReset();


  // Test 12
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Tiny Font:"));
  myOLED.setFontNum(CH1115Font_Tiny);
  myOLED.setCursor(0, 15);
  myOLED.print(F("tiny FONT 9837*!"));
  myOLED.drawChar(150, 25, 't', OLED_WHITE, OLED_BLACK, 3);
  myOLED.setCursor(0, 40);
  myOLED.setTextSize(2);
  myOLED.print(3.144445, 2);

  TestReset();


  // Test 13
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("homespun Font:"));
  myOLED.setFontNum(CH1115Font_Homespun);
  myOLED.setCursor(0, 15);
  myOLED.print(F("Homespun 32*!"));
  myOLED.drawChar(150, 25, 'h', OLED_WHITE, OLED_BLACK, 3);
  myOLED.setCursor(0, 40);
  myOLED.setTextSize(2);
  myOLED.print(7.15);

  TestReset();
}

void DisplayFontsTwo(void) {
  char myString[9] = { '1', '3', ':', '2', '6', ':', '1', '8' };
  uint16_t countUp = 0;
  myOLED.setTextColor(OLED_WHITE, OLED_BLACK);

  // Test 14
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("big nums Font:"));
  myOLED.setFontNum(CH1115Font_Bignum);
  myOLED.setCursor(0, 15);
  myOLED.print(6.05);  // Test 14a print a Float
  myOLED.setCursor(80, 15);
  myOLED.print(-2);  // Test 14a print a negative number

  TestReset();

  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE);  // Test 14b drawText , 13:26:18 inverted
  myOLED.drawChar(0, 0, '8', OLED_WHITE, OLED_BLACK);        // Test 14c drawChar
  myOLED.drawChar(90, 0, '4', OLED_BLACK, OLED_WHITE);      // Test 14d drawChar inverted

  TestReset();
  while (countUp < MYCOUNT_UPTIME)  // Show a count 14e
  {
    myOLED.setCursor(0, 0);
    myOLED.print(countUp++);
    myOLED.OLEDupdate();
  }
  TestReset();

  //test 15
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("med nums Font:"));
  myOLED.setFontNum(CH1115Font_Mednum);
  myOLED.setCursor(0, 15);
  myOLED.print(6.43);  // Test 15a print a Float
  myOLED.setCursor(0, 32);
  myOLED.print(-95);  // Test 14a print a negative number

  TestReset();

  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE);  // Test 15b drawText , 13:26:18 inverted
  myOLED.drawChar(0, 0, '8', OLED_WHITE, OLED_BLACK);        // Test 15c drawChar
  myOLED.drawChar(90, 0, '4', OLED_BLACK, OLED_WHITE);      // Test 15d drawChar inverted

  TestReset();
  countUp = 0;
  while (countUp < MYCOUNT_UPTIME)  // Show a count 15e
  {
    myOLED.setCursor(0, 0);
    myOLED.print(countUp++);
    myOLED.OLEDupdate();
  }
  TestReset();

  // Test 16 Arial round Font
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Arial Round Font:"));
  myOLED.setFontNum(CH1115Font_ArialRound);
  myOLED.setCursor(0, 15);
  myOLED.print(-16.05);
  myOLED.setCursor(0, 40);
  myOLED.print("Arial R");

  TestReset();

  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE);
  myOLED.drawChar(0, 0, 'A', OLED_WHITE, OLED_BLACK);
  myOLED.drawChar(90, 0, 'R', OLED_BLACK, OLED_WHITE);

  TestReset();

  // Test 17 Arial bold Font
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Arial bold font:"));
  myOLED.setFontNum(CH1115Font_ArialBold);
  myOLED.setCursor(0, 15);
  myOLED.print(-17.05);
  myOLED.setCursor(0, 40);
  myOLED.print("Arial b");

  TestReset();

  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE);
  myOLED.drawChar(0, 0, 'A', OLED_WHITE, OLED_BLACK);
  myOLED.drawChar(90, 0, 'B', OLED_BLACK, OLED_WHITE);

  TestReset();

  // Test 18 Mia font
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Mia Font:"));
  myOLED.setFontNum(CH1115Font_Mia);
  myOLED.setCursor(0, 15);
  myOLED.print(-18.05);
  myOLED.setCursor(0, 40);
  myOLED.print("Mia Font");

  TestReset();

  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE);
  myOLED.drawChar(0, 0, 'M', OLED_WHITE, OLED_BLACK);
  myOLED.drawChar(90, 0, 'A', OLED_BLACK, OLED_WHITE);

  TestReset();

  // Test 19 Dedica Font
  myOLED.setCursor(0, 0);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.setTextSize(1);
  myOLED.print(F("Dedica Font:"));
  myOLED.setFontNum(CH1115Font_Mia);
  myOLED.setCursor(0, 15);
  myOLED.setTextColor(OLED_WHITE, OLED_BLACK);
  myOLED.print(-18.05);
  myOLED.setCursor(0, 40);
  myOLED.print("Dedica Font");

  TestReset();

  myOLED.drawText(0, 32, myString, OLED_BLACK, OLED_WHITE);
  myOLED.drawChar(0, 0, 'D', OLED_WHITE, OLED_BLACK);
  myOLED.drawChar(90, 0, 'F', OLED_BLACK, OLED_WHITE);
  TestReset();
}

// Test 20 Error Checking
// Excepted Ouput
// 11:53:55.109 -> Test 20-A drawChar
// 11:53:55.109 -> 02334
// 11:54:00.343 -> Test 20-A drawText
// 11:54:00.343 -> 0245
// 11:54:05.606 -> Test 20-B drawChar
// 11:54:05.606 -> 02334
// 11:54:10.842 -> Test 20-B drawText
// 11:54:10.842 -> 0254
void ErrorChecking(void) {

  char myStringPASS[] = "WIDE";
  char myStringFAIL[] = "WIzDE";  // Wide font has no lowercase letters
  char* myStringNull = nullptr;

  //20-A font 1-6
  //drawchar
  myOLED.setFontNum(CH1115Font_Wide);
  Serial.println("Test 20-A drawChar");
  Serial.print(myOLED.drawChar(0, 0, 'W', OLED_WHITE, OLED_BLACK, 1));     // OLED_Success = 0
  Serial.print(myOLED.drawChar(20, 0, 'W', OLED_WHITE, OLED_BLACK));       // OLED_WrongFont = 2
  Serial.print(myOLED.drawChar(150, 0, 'W', OLED_WHITE, OLED_BLACK, 1));   // OLED_CharScreenBounds = 3
  Serial.print(myOLED.drawChar(0, 80, 'W', OLED_WHITE, OLED_BLACK, 1));   // OLED_CharScreenBounds = 3
  Serial.println(myOLED.drawChar(23, 0, 'z', OLED_WHITE, OLED_BLACK, 1));  // OLED_CharFontASCIIRange = 4
  TestReset();

  //drawText
  Serial.println("Test 20-A drawText");
  Serial.print(myOLED.drawText(0, 0, myStringPASS, OLED_WHITE, OLED_BLACK, 1));     // OLED_Success = 0
  Serial.print(myOLED.drawText(0, 20, myStringPASS, OLED_WHITE, OLED_BLACK));       // OLED_WrongFont = 2
  Serial.print(myOLED.drawText(0, 40, myStringFAIL, OLED_WHITE, OLED_BLACK, 1));    // OLED_CharFontASCIIRange = 4
  Serial.println(myOLED.drawText(0, 40, myStringNull, OLED_WHITE, OLED_BLACK, 1));  // OLED_CharArrayNullptr = 5
  TestReset();

  //Test 20-b fotns 7-12
  //drawchar
  Serial.println("Test 20-B drawChar");
  myOLED.setFontNum(CH1115Font_Mednum);
  Serial.print(myOLED.drawChar(0, 0, '1', OLED_WHITE, OLED_BLACK));      // OLED_Success = 0
  Serial.print(myOLED.drawChar(20, 0, '2', OLED_WHITE, OLED_BLACK, 1));  // OLED_WrongFont = 2
  Serial.print(myOLED.drawChar(150, 0, '3', OLED_WHITE, OLED_BLACK));    // OLED_CharScreenBounds = 3
  Serial.print(myOLED.drawChar(0, 80, '4', OLED_WHITE, OLED_BLACK));    // OLED_CharScreenBounds = 3
  Serial.println(myOLED.drawChar(23, 0, 'z', OLED_WHITE, OLED_BLACK));   // OLED_CharFontASCIIRange = 4
  TestReset();

  //drawText
  Serial.println("Test 20-B drawText");
  myOLED.setFontNum(CH1115Font_ArialBold);
  Serial.print(myOLED.drawText(0, 0, myStringPASS, OLED_WHITE, OLED_BLACK));      // OLED_Success = 0
  Serial.print(myOLED.drawText(0, 20, myStringPASS, OLED_WHITE, OLED_BLACK, 1));  // OLED_WrongFont = 2
  Serial.print(myOLED.drawText(0, 40, myStringNull, OLED_WHITE, OLED_BLACK));     // OLED_CharArrayNullptr = 5
  myOLED.setFontNum(CH1115Font_Mednum);
  Serial.println(myOLED.drawText(0, 40, myStringFAIL, OLED_WHITE, OLED_BLACK));  // OLED_CharFontASCIIRange = 4
  TestReset();
}

void TestReset(void) {
  myOLED.OLEDupdate();  // Write to the buffer
  delay(DisplayDelay5);
  myOLED.OLEDclearBuffer();
}
// ************** EOF **************
