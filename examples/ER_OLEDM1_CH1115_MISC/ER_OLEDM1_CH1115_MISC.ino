
// Example file name : ER_OLEDM1_CH1115_Misc.ino
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing use of various function
//
//  (1) Enable and disable Screen (Sleep mode , 500uA)
//  (2) Invert screen colour
//  (3) Rotate vertically screen 180 (flip ~ invert)
//  (4) Contrast screen
//  (5) Scroll Screen
//  (6) Fade effect
//
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
// *****************************
// NOTES :
// (1) GPIO is for arduino UNO for other tested MCU see readme
// (2) In the <ER_OLEDM1_CH1115.h> USER BUFFER OPTION SECTION at top of file
// , option MULTI_BUFFER must be selected
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
  myOLED.OLEDbegin();             // initialize the OLED
  myOLED.OLEDFillScreen(0x00, 0); // Clears screen
}

// *********** MAIN LOOP ******************
void loop()
{
  // Define a full screen buffer and struct
  uint8_t  screenBuffer[myOLEDwidth * (myOLEDheight / 8) ];

  MultiBuffer whole_screen;
  whole_screen.screenbitmap = (uint8_t*) &screenBuffer;
  whole_screen.width = myOLEDwidth;
  whole_screen.height = myOLEDheight;
  whole_screen.xoffset = 0;
  whole_screen.yoffset = 0;

  myOLED.ActiveBuffer =  &whole_screen; // set buffer object
  myOLED.OLEDclearBuffer(); // clear the buffer
  
  // Set text parameters
  myOLED.setTextColor(FOREGROUND);
  myOLED.setTextSize(1);
 
  
  //  ** Test1 OLED enable and disable **
  myOLED.setCursor(0, 30);
  myOLED.print("OLED Disable test 1");
  myOLED.OLEDupdate();
  
  delay(3000); //display message
  myOLED.OLEDEnable(0); //turn off display (sleep mode 500uA measured)
  delay(3000); //wait for 3
  myOLED.OLEDEnable(1); //turn on
  delay(2000); //display message
  myOLED.OLEDclearBuffer();

  // ** Test 2 inverse **
  myOLED.setCursor(0, 10);
  myOLED.print("OLED Inverse test 2");
  myOLED.OLEDupdate();
  delay(3000);
  myOLED.OLEDInvert(1); // Inverted
  delay(5000);
  myOLED.OLEDInvert(0);
  delay(1000);


  // ** Test3 OLED flip **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  myOLED.print("Flip test 3");
  myOLED.OLEDupdate();
  delay(4000);
  myOLED.OLEDFlip(1);
  delay(4000);
  myOLED.OLEDFlip(0);
  delay(2000);

  // ** Test 4 contrast **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 0);
  myOLED.print("Contrast test 4");
  myOLED.OLEDupdate();
  delay(2500);
  myOLED.OLEDFillScreen(0x77, 0); // fill screen

  myOLED.OLEDContrast(0x00);
  delay(1000);
  myOLED.OLEDContrast(0x80);
  delay(1000);
  myOLED.OLEDContrast(0xFF);
  delay(1000);
  myOLED.OLEDContrast(OLEDcontrast);
  delay(1000);
  myOLED.OLEDclearBuffer();


  // ** Test5 OLED scroll **
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(0, 40);
  myOLED.print("Scroll test 5 ");
  myOLED.OLEDupdate();
  delay(2500);
  
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

  // ** TEST 6 fade ~ breath effect **
  myOLED.OLEDclearBuffer();
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  myOLED.print("Fade effect test 6");
  myOLED.OLEDupdate();
  delay(3000);
  myOLED.OLEDfadeEffect();
  myOLED.OLEDFillScreen(0xE3, 0);
  delay(10000);
  myOLED.OLEDfadeEffect(0x00); // switch off fade
  
  myOLED.OLEDclearBuffer();
  myOLED.setCursor(5, 5);
  
  myOLED.print("End of tests");
  myOLED.OLEDupdate();
  delay(5000);
  myOLED.OLEDEnable(0); // TURN OFF DISPLAY when finshed 
  while (1)
  {
    delay(1); // tests over, loop here forever
  }
}

// *********** END OF MAIN ***********
