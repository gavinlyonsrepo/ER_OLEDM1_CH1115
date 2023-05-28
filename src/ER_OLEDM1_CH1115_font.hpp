/*!
	@file ER_OLEDM1_CH1115_font.hpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller font  header file , 
	Project Name: ER_OLEDM1_CH1115 , URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@author  Gavin Lyons
*/

#ifndef  _ER_OLEDM1_CH1115_font_H
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

#define CH1115_Font_One       /**<  (1) default  (FUll ASCII with mods) */
//#define CH1115_Font_Two       /**<  (2) thick (NO LOWERCASE) */
//#define CH1115_Font_Three    /**<  (3) seven segment  */
//#define CH1115_Font_Four     /**<  (4) wide (NO LOWERCASE) */
//#define CH1115_Font_Five      /**<  (5) tiny */
//#define CH1115_Font_Six       /**<  (6) HomeSpun */
//#define CH1115_Font_Seven  /**< (7) big numbers (NUMBERS ONLY ) */
//#define CH1115_Font_Eight   /**< (8) Med numbers (NUMBERS ONLY ) */

// ****** END OF FONT DEFINE SECTION ******  
// **********************************************


// Font data is in the cpp file accessed thru extern pointers.

#ifdef CH1115_Font_One 
extern const unsigned char * pFontDefaultptr;   /**<  Pointer to the default font*/
#endif
#ifdef CH1115_Font_Two 
extern const unsigned char * pFontThickptr;  /**<  Pointer to the Thick font*/
#endif
#ifdef CH1115_Font_Three
extern const unsigned char * pFontSevenSegptr; /**<  Pointer to the Seven segment font*/
#endif
#ifdef CH1115_Font_Four
extern const unsigned char * pFontWideptr; /**<  Pointer to the Wide font*/
#endif
#ifdef CH1115_Font_Five
extern const  unsigned char * pFontTinyptr;  /**<  Pointer to the Tiny font*/
#endif
#ifdef CH1115_Font_Six
extern const unsigned char * pFontHomeSpunptr;   /**<  Pointer to the Homespun font*/
#endif
#ifdef CH1115_Font_Seven
extern const uint8_t (* pFontBigNumptr)[64];  /**<  Pointer to the Big numbers font*/
#endif
#ifdef CH1115_Font_Eight
extern const uint8_t (* pFontMedNumptr)[32];  /**<  Pointer to the Medium numbers font*/
#endif


#endif // guard header
