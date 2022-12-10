/*
* Project Name: ER_OLEDM1_CH1115
* File: ER_OLEDM1_CH1115_font.hpp
* Description: ER_OLEDM1 OLED driven by CH1115 controller font file 
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
*/

#ifndef _ER_OLEDM1_CH1115_font_H
#define _ER_OLEDM1_CH1115_font_H

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifdef __AVR__
 #include <avr/io.h>
 #include <avr/pgmspace.h>
#else
#ifndef ESP8266
 #define PROGMEM
#endif
#endif

// **********************************************
// ****** USER FONT OPTION ONE *************
// ****** FONT DEFINE SECTION *************** 
// Comment in the fonts YOU want, One is default. 

#define CH1115_Font_One  // (1) default  (FUll ASCII with mods)
//#define CH1115_Font_Two  // (2) thick (NO LOWERCASE)
//#define CH1115_Font_Three // (3) seven segment 
//#define CH1115_Font_Four // (4) wide (NO LOWERCASE)
//#define CH1115_Font_Five // (5) tiny
//#define CH1115_Font_Six // (6) HomeSpun
//#define CH1115_Font_Seven // (7) big numbers (NUMBERS ONLY )
//#define CH1115_Font_Eight // (8) Med numbers (NUMBERS ONLY )

// ****** END OF FONT DEFINE SECTION ******  
// **********************************************


// Font data is in the cpp file accessed thru extern pointers.

#ifdef CH1115_Font_One 
extern const unsigned char * pFontDefaultptr;
#endif
#ifdef CH1115_Font_Two 
extern const unsigned char * pFontThickptr;
#endif
#ifdef CH1115_Font_Three
extern const unsigned char * pFontSevenSegptr;
#endif
#ifdef CH1115_Font_Four
extern const unsigned char * pFontWideptr;
#endif
#ifdef CH1115_Font_Five
extern const  unsigned char * pFontTinyptr;
#endif
#ifdef CH1115_Font_Six
extern const unsigned char * pFontHomeSpunptr;
#endif
#ifdef CH1115_Font_Seven
extern const uint8_t (* pFontBigNumptr)[64];
#endif
#ifdef CH1115_Font_Eight
extern const uint8_t (* pFontMedNumptr)[32]; 
#endif


#endif // guard header
