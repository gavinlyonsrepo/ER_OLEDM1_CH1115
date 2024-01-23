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

/*!
	@brief USER FONT OPTION ONE , FONT DEFINE SECTION 
	@note Comment in the fonts YOU want, CH1115_Font_One is default. 
		-#  CH1115_Font_One  default  (FUll ASCII with mods)
		-#  CH1115_Font_Two  thick (NO LOWERCASE)
		-#  CH1115_Font_Three seven segment 
		-#  CH1115_Font_Four wide (NO LOWERCASE)
		-#  CH1115_Font_Five  tiny
		-#  CH1115_Font_Six Home Spun
		-#  CH1115_Font_Seven big numbers ( extended Numeric )
		-#  CH1115_Font_Eight Medium numbers (extended Numeric )
		-#  CH1115_Font_Nine Arial round
		-#  CH1115_Font_Ten  Arial bold
		-# CH1115_Font_Eleven  Mia
		-# CH1115_Font_Twelve  dedica
*/

#define CH1115_Font_One         /**< (1) default  (FUll ASCII with mods) */ 
//#define CH1115_Font_Two       /**< (2) thick (NO LOWERCASE) */
//#define CH1115_Font_Three    /**<  (3) seven segment  */
//#define CH1115_Font_Four      /**<  (4) wide (NO LOWERCASE) */
//#define CH1115_Font_Five      /**< (5) tiny */
//#define CH1115_Font_Six       /**< (6) HomeSpun */
//#define CH1115_Font_Seven /**<  (7) big numbers ( extended Numeric )*/
//#define CH1115_Font_Eight /**< (8) Med numbers (extended Numeric )*/
//#define CH1115_Font_Nine /**< (9) Arial round*/
//#define CH1115_Font_Ten  /**<  (10) Arial bold*/
//#define CH1115_Font_Eleven /**< (11) Mia*/
//#define CH1115_Font_Twelve  /**< (12) dedica*/


// Font data is in the cpp file accessed thru extern pointers.

#ifdef CH1115_Font_One 
extern const unsigned char * pFontDefaultptr; /**< Pointer to Default  font data */
#endif
#ifdef CH1115_Font_Two 
extern const unsigned char * pFontThickptr; /**< Pointer to thick font data */
#endif
#ifdef CH1115_Font_Three
extern const unsigned char * pFontSevenSegptr; /**< Pointer to Seven segment font data */
#endif
#ifdef CH1115_Font_Four
extern const unsigned char * pFontWideptr; /**< Pointer to Wide font data */
#endif
#ifdef CH1115_Font_Five
extern const  unsigned char * pFontTinyptr; /**< Pointer to Tiny font data */
#endif
#ifdef CH1115_Font_Six
extern const unsigned char * pFontHomeSpunptr; /**< Pointer to Home Spun font data */
#endif
#ifdef CH1115_Font_Seven
extern const uint8_t (* pFontBigNum16x32ptr)[64]; /**< Pointer to Big Numbers font data */
#endif
#ifdef CH1115_Font_Eight
extern const uint8_t (* pFontMedNum16x16ptr)[32];  /**< Pointer to Medium  Numbers font data */
#endif
#ifdef CH1115_Font_Nine
extern const uint8_t (* pFontArial16x24ptr)[48]; /**< Pointer to Arial Round font data */
#endif
#ifdef CH1115_Font_Ten
extern const uint8_t (* pFontArial16x16ptr)[32]; /**< Pointer to Arial bold font data */
#endif
#ifdef CH1115_Font_Eleven
extern const uint8_t (* pFontMia8x16ptr)[16]; /**< Pointer to Mia font data */
#endif
#ifdef CH1115_Font_Twelve
extern const uint8_t (* pFontDedica8x12ptr)[12]; /**< Pointer to dedica font data */
#endif


#endif // guard header
