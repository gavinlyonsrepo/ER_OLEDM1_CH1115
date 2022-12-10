
// Example file name : ER_OLEDM1_CH1115_NOBUFFER.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of "No buffer" mode .
// in this mode the OLED can be used as a relatively light weight character OLED
// 8 rows and 144 characters, 7by8 ,font size (128/7 * 64/8 ),
// you can also write bitmaps directly to screen in this mode.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme.
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION, at top of file
// option NO_BUFFER must be selected and only this option.
// (3) This is for hardware SPI for software SPI see ER_OLEDM1_CH1115_SWSPI.ino example.
// (4) Test 5.  (needs UC_FONT_MOD_TWO to be commented in (default) , in font file)
// ******************

#include "ER_OLEDM1_CH1115.hpp"

#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. user adjust

// GPIO 5-wire SPI interface
#define RES 8 // GPIO pin number pick any you want
#define DC 9 // GPIO pin number pick any you want 
#define CS 10  // GPIO pin number pick any you want
// GPIO pin number SCK(UNO 13) , HW SPI , SCK
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI

ERMCH1115  myOLED(DC, RES, CS); // object , DC, RES, CS


// 'small image', 20x20px
const   PROGMEM  uint8_t smallImage [] = {
  0xff, 0x3f, 0x0f, 0x07, 0x03, 0x13, 0x33, 0x39, 0x39, 0x79, 0xf9, 0xf9, 0xfb, 0xf3, 0xf7, 0xe3,
  0x87, 0x0f, 0x1f, 0xff, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f,
  0x1d, 0x19, 0x10, 0x19, 0x0f, 0x00, 0xc0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x0c, 0x08, 0x08,
  0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f
};

// ************* SETUP ***************
void setup()
{
  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x33, 0); // Fill screen with effect
  delay(500);
}

// ************** MAIN LOOP ***********
void loop() {
  while (1)
  {
    Tests();
  }
}
// ************** END OF MAIN ***********

//Function to run a group of tests
// Test 0 clear screen
// Test 0.5 bitmap
// Test 1 String function and goto function
// Test 2 clear page function
// Test 3 character function
// Test 4 print entire ASCII font with character function 0-127
// Test 5 print extended ASCII (needs UC_FONT_MOD_TWO to be commented in (default) , in font file)

void Tests()
{


  //Test 0 clear screen

  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen
  delay(500);

  // Test0.5 bitmap
  myOLED.OLEDBitmap(10, 10 , 20, 20, smallImage);
  delay(2000);

  unsigned char test0_1[] = "This is page 0";
  unsigned char test1_2[] = "123456789012345678";
  unsigned char test1_3[] = "This is page 7";

  // Test 1 String function and goto function
  myOLED.OLEDNoBufferGotoXY(0, 0); // (Col , page ) Col 0 to 191 , page 0 to 7
  myOLED.OLEDNoBufferString(test0_1); // Write a character string
  myOLED.OLEDNoBufferGotoXY(0, 4);
  myOLED.OLEDNoBufferString(test1_2);
  myOLED.OLEDNoBufferGotoXY(0, 7);
  myOLED.OLEDNoBufferString(test1_3);
  delay(5000);

  // Test 2 clear page function

  myOLED.OLEDFillPage(7, 0x00, 0); // Clear page
  myOLED.OLEDFillPage(6, 0x7E, 0); // Write pattern (0111 1110) to a page
  delay(5000);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen

  // Test 3 character function
  myOLED.OLEDNoBufferGotoXY(100, 2);
  myOLED.OLEDNoBufferChar('H');  // write single  character
  myOLED.OLEDNoBufferChar('2');
  delay(2000);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen

  // Test 4 print entire font with character function
  // NOTE For characters 32-127 for charcters comment in UC_FONT_MOD_ONE  n font file ER_OLEDM1_CH1115_font.h.
  myOLED.OLEDNoBufferGotoXY(0, 0);
  uint8_t row = 1;
  char offset = 32;

  for (unsigned char i = 0; i < 126 ; i++)
  {
    if (i % 18 == 0) myOLED.OLEDNoBufferGotoXY(0, row++);
    myOLED.OLEDNoBufferChar(i);
    delay(5);
  }
  delay(3000);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen

  // TEST 5 print ASCII font 128-255 with character function
  // For characters after 'z{|}' in ASCII table user can comment in UC_FONT_MOD_TWO in font file
  // (NOTE: this will increase program size)
  myOLED.OLEDNoBufferGotoXY(0, 0);
  row = 1;
  for (unsigned char k = 128; k < 255 ; k++)
  {
    if (k % 18 == 0) myOLED.OLEDNoBufferGotoXY(0, row++);
    myOLED.OLEDNoBufferChar(k);
    delay(5);
  }
  delay(3000);
  myOLED.OLEDFillScreen(0x00, 0); // Clear the screen

}
