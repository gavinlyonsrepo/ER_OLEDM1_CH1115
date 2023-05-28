/*!
	@file ER_OLEDM1_CH1115_font.cpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller font  data file , 
	Project Name: ER_OLEDM1_CH1115 , URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@author  Gavin Lyons
*/

#include "ER_OLEDM1_CH1115_font.hpp"

#ifdef CH1115_Font_One

// *******USER FONT OPTION TWO *************
/*! Comment this define  UC_FONT_MOD_TWO  to decrease size of full ASCII font.
(saves 640 bytes) removes extended ASCII 127-255 */
#define UC_FONT_MOD_TWO 
//***********************************************

// Standard ASCII 5x7 font ,default.
static const  PROGMEM  unsigned char CH_Font_One[]  = {
   0x00, 0x00, 0x00, 0x00, 0x00,   
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,  // :)
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E, 
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C, 
	0x18, 0x3C, 0x7E, 0x3C, 0x18, 
	0x1C, 0x57, 0x7D, 0x57, 0x1C, 
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C, 
	0x00, 0x18, 0x3C, 0x18, 0x00, 
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF, 
	0x00, 0x18, 0x24, 0x18, 0x00, 
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF, 
	0x30, 0x48, 0x3A, 0x06, 0x0E, 
	0x26, 0x29, 0x79, 0x29, 0x26, 
	0x40, 0x7F, 0x05, 0x05, 0x07, 
	0x40, 0x7F, 0x05, 0x25, 0x3F, 
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A, 
	0x7F, 0x3E, 0x1C, 0x1C, 0x08, 
	0x08, 0x1C, 0x1C, 0x3E, 0x7F, 
	0x14, 0x22, 0x7F, 0x22, 0x14, 
	0x5F, 0x5F, 0x00, 0x5F, 0x5F, 
	0x06, 0x09, 0x7F, 0x01, 0x7F, 
	0x00, 0x66, 0x89, 0x95, 0x6A, 
	0x60, 0x60, 0x60, 0x60, 0x60, 
	0x94, 0xA2, 0xFF, 0xA2, 0x94, 
	0x08, 0x04, 0x7E, 0x04, 0x08, 
	0x10, 0x20, 0x7E, 0x20, 0x10, 
	0x08, 0x08, 0x2A, 0x1C, 0x08, 
	0x08, 0x1C, 0x2A, 0x08, 0x08, 
	0x1E, 0x10, 0x10, 0x10, 0x10, 
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C, 
	0x30, 0x38, 0x3E, 0x38, 0x30, 
	0x06, 0x0E, 0x3E, 0x0E, 0x06, 
	0x00, 0x00, 0x00, 0x00, 0x00,  // Space
	0x00, 0x00, 0x5F, 0x00, 0x00,  // !
	0x00, 0x07, 0x00, 0x07, 0x00, 
	0x14, 0x7F, 0x14, 0x7F, 0x14, 
	0x24, 0x2A, 0x7F, 0x2A, 0x12, 
	0x23, 0x13, 0x08, 0x64, 0x62, 
	0x36, 0x49, 0x56, 0x20, 0x50, 
	0x00, 0x08, 0x07, 0x03, 0x00, 
	0x00, 0x1C, 0x22, 0x41, 0x00, 
	0x00, 0x41, 0x22, 0x1C, 0x00, 
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 
	0x08, 0x08, 0x3E, 0x08, 0x08, 
	0x00, 0x80, 0x70, 0x30, 0x00, 
	0x08, 0x08, 0x08, 0x08, 0x08, 
	0x00, 0x00, 0x60, 0x60, 0x00, 
	0x20, 0x10, 0x08, 0x04, 0x02, 
	0x3E, 0x51, 0x49, 0x45, 0x3E, 
	0x00, 0x42, 0x7F, 0x40, 0x00, 
	0x72, 0x49, 0x49, 0x49, 0x46, 
	0x21, 0x41, 0x49, 0x4D, 0x33, 
	0x18, 0x14, 0x12, 0x7F, 0x10, 
	0x27, 0x45, 0x45, 0x45, 0x39, 
	0x3C, 0x4A, 0x49, 0x49, 0x31, 
	0x41, 0x21, 0x11, 0x09, 0x07, 
	0x36, 0x49, 0x49, 0x49, 0x36, 
	0x46, 0x49, 0x49, 0x29, 0x1E, 
	0x00, 0x00, 0x14, 0x00, 0x00, 
	0x00, 0x40, 0x34, 0x00, 0x00, 
	0x00, 0x08, 0x14, 0x22, 0x41, 
	0x14, 0x14, 0x14, 0x14, 0x14, 
	0x00, 0x41, 0x22, 0x14, 0x08, 
	0x02, 0x01, 0x59, 0x09, 0x06, 
	0x3E, 0x41, 0x5D, 0x59, 0x4E, 
	0x7C, 0x12, 0x11, 0x12, 0x7C, 
	0x7F, 0x49, 0x49, 0x49, 0x36, 
	0x3E, 0x41, 0x41, 0x41, 0x22, 
	0x7F, 0x41, 0x41, 0x41, 0x3E, 
	0x7F, 0x49, 0x49, 0x49, 0x41, 
	0x7F, 0x09, 0x09, 0x09, 0x01, 
	0x3E, 0x41, 0x41, 0x51, 0x73, 
	0x7F, 0x08, 0x08, 0x08, 0x7F, 
	0x00, 0x41, 0x7F, 0x41, 0x00, 
	0x20, 0x40, 0x41, 0x3F, 0x01, 
	0x7F, 0x08, 0x14, 0x22, 0x41, 
	0x7F, 0x40, 0x40, 0x40, 0x40, 
	0x7F, 0x02, 0x1C, 0x02, 0x7F, 
	0x7F, 0x04, 0x08, 0x10, 0x7F, 
	0x3E, 0x41, 0x41, 0x41, 0x3E, 
	0x7F, 0x09, 0x09, 0x09, 0x06, 
	0x3E, 0x41, 0x51, 0x21, 0x5E, 
	0x7F, 0x09, 0x19, 0x29, 0x46, 
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03, 
	0x3F, 0x40, 0x40, 0x40, 0x3F, 
	0x1F, 0x20, 0x40, 0x20, 0x1F, 
	0x3F, 0x40, 0x38, 0x40, 0x3F, 
	0x63, 0x14, 0x08, 0x14, 0x63, 
	0x03, 0x04, 0x78, 0x04, 0x03, 
	0x61, 0x59, 0x49, 0x4D, 0x43, 
	0x00, 0x7F, 0x41, 0x41, 0x41, 
	0x02, 0x04, 0x08, 0x10, 0x20, 
	0x00, 0x41, 0x41, 0x41, 0x7F, 
	0x04, 0x02, 0x01, 0x02, 0x04,
    0x40, 0x40, 0x40, 0x40, 0x40, 
    0x00, 0x03, 0x07, 0x08, 0x00, 
	0x20, 0x54, 0x54, 0x78, 0x40, 
	0x7F, 0x28, 0x44, 0x44, 0x38, 
	0x38, 0x44, 0x44, 0x44, 0x28, 
	0x38, 0x44, 0x44, 0x28, 0x7F, 
	0x38, 0x54, 0x54, 0x54, 0x18, 
	0x00, 0x08, 0x7E, 0x09, 0x02, 
	0x18, 0xA4, 0xA4, 0x9C, 0x78, 
	0x7F, 0x08, 0x04, 0x04, 0x78, 
	0x00, 0x44, 0x7D, 0x40, 0x00, 
	0x20, 0x40, 0x40, 0x3D, 0x00, 
	0x7F, 0x10, 0x28, 0x44, 0x00, 
	0x00, 0x41, 0x7F, 0x40, 0x00, 
	0x7C, 0x04, 0x78, 0x04, 0x78, 
	0x7C, 0x08, 0x04, 0x04, 0x78, 
	0x38, 0x44, 0x44, 0x44, 0x38, 
	0xFC, 0x18, 0x24, 0x24, 0x18, 
	0x18, 0x24, 0x24, 0x18, 0xFC, 
	0x7C, 0x08, 0x04, 0x04, 0x08, 
	0x48, 0x54, 0x54, 0x54, 0x24, 
	0x04, 0x04, 0x3F, 0x44, 0x24, 
	0x3C, 0x40, 0x40, 0x20, 0x7C, 
	0x1C, 0x20, 0x40, 0x20, 0x1C, 
	0x3C, 0x40, 0x30, 0x40, 0x3C, 
	0x44, 0x28, 0x10, 0x28, 0x44, 
	0x4C, 0x90, 0x90, 0x90, 0x7C, 
	0x44, 0x64, 0x54, 0x4C, 0x44,  // z
	0x00, 0x08, 0x36, 0x41, 0x00, // {
	0x00, 0x00, 0x77, 0x00, 0x00, // |
	0x00, 0x41, 0x36, 0x08, 0x00  // }
#ifdef UC_FONT_MOD_TWO
	,0x02, 0x01, 0x02, 0x04, 0x02, // capital letter c with cedilla
	0x3C, 0x26, 0x23, 0x26, 0x3C, 
	0x1E, 0xA1, 0xA1, 0x61, 0x12, 
	0x3A, 0x40, 0x40, 0x20, 0x7A, 
	0x38, 0x54, 0x54, 0x55, 0x59, 
	0x21, 0x55, 0x55, 0x79, 0x41, 
	0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
	0x21, 0x55, 0x54, 0x78, 0x40, 
	0x20, 0x54, 0x55, 0x79, 0x40, 
	0x0C, 0x1E, 0x52, 0x72, 0x12, 
	0x39, 0x55, 0x55, 0x55, 0x59, 
	0x39, 0x54, 0x54, 0x54, 0x59, 
	0x39, 0x55, 0x54, 0x54, 0x58, 
	0x00, 0x00, 0x45, 0x7C, 0x41, 
	0x00, 0x02, 0x45, 0x7D, 0x42, 
	0x00, 0x01, 0x45, 0x7C, 0x40, 
	0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut
	0xF0, 0x28, 0x25, 0x28, 0xF0, 
	0x7C, 0x54, 0x55, 0x45, 0x00, 
	0x20, 0x54, 0x54, 0x7C, 0x54, 
	0x7C, 0x0A, 0x09, 0x7F, 0x49, 
	0x32, 0x49, 0x49, 0x49, 0x32, 
	0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
	0x32, 0x4A, 0x48, 0x48, 0x30, 
	0x3A, 0x41, 0x41, 0x21, 0x7A, 
	0x3A, 0x42, 0x40, 0x20, 0x78, 
	0x00, 0x9D, 0xA0, 0xA0, 0x7D, 
	0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
	0x3D, 0x40, 0x40, 0x40, 0x3D, 
	0x3C, 0x24, 0xFF, 0x24, 0x24, 
	0x48, 0x7E, 0x49, 0x43, 0x66, 
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B, 
	0xFF, 0x09, 0x29, 0xF6, 0x20, 
	0xC0, 0x88, 0x7E, 0x09, 0x03, 
	0x20, 0x54, 0x54, 0x79, 0x41, 
	0x00, 0x00, 0x44, 0x7D, 0x41, 
	0x30, 0x48, 0x48, 0x4A, 0x32, 
	0x38, 0x40, 0x40, 0x22, 0x7A, 
	0x00, 0x7A, 0x0A, 0x0A, 0x72, 
	0x7D, 0x0D, 0x19, 0x31, 0x7D, 
	0x26, 0x29, 0x29, 0x2F, 0x28, 
	0x26, 0x29, 0x29, 0x29, 0x26, 
	0x30, 0x48, 0x4D, 0x40, 0x20, 
	0x38, 0x08, 0x08, 0x08, 0x08, 
	0x08, 0x08, 0x08, 0x08, 0x38, 
	0x2F, 0x10, 0xC8, 0xAC, 0xBA, 
	0x2F, 0x10, 0x28, 0x34, 0xFA, 
	0x00, 0x00, 0x7B, 0x00, 0x00, 
	0x08, 0x14, 0x2A, 0x14, 0x22, 
	0x22, 0x14, 0x2A, 0x14, 0x08, 
	0xAA, 0x00, 0x55, 0x00, 0xAA, 
	0xAA, 0x55, 0xAA, 0x55, 0xAA, 
	0x00, 0x00, 0x00, 0xFF, 0x00, 
	0x10, 0x10, 0x10, 0xFF, 0x00, 
	0x14, 0x14, 0x14, 0xFF, 0x00, 
	0x10, 0x10, 0xFF, 0x00, 0xFF, 
	0x10, 0x10, 0xF0, 0x10, 0xF0, 
	0x14, 0x14, 0x14, 0xFC, 0x00, 
	0x14, 0x14, 0xF7, 0x00, 0xFF, 
	0x00, 0x00, 0xFF, 0x00, 0xFF, 
	0x14, 0x14, 0xF4, 0x04, 0xFC, 
	0x14, 0x14, 0x17, 0x10, 0x1F, 
	0x10, 0x10, 0x1F, 0x10, 0x1F, 
	0x14, 0x14, 0x14, 0x1F, 0x00, 
	0x10, 0x10, 0x10, 0xF0, 0x00, 
	0x00, 0x00, 0x00, 0x1F, 0x10, 
	0x10, 0x10, 0x10, 0x1F, 0x10, 
	0x10, 0x10, 0x10, 0xF0, 0x10, 
	0x00, 0x00, 0x00, 0xFF, 0x10, 
	0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x10, 0xFF, 0x10, 
	0x00, 0x00, 0x00, 0xFF, 0x14, 
	0x00, 0x00, 0xFF, 0x00, 0xFF, 
	0x00, 0x00, 0x1F, 0x10, 0x17, 
	0x00, 0x00, 0xFC, 0x04, 0xF4, 
	0x14, 0x14, 0x17, 0x10, 0x17, 
	0x14, 0x14, 0xF4, 0x04, 0xF4, 
	0x00, 0x00, 0xFF, 0x00, 0xF7, 
	0x14, 0x14, 0x14, 0x14, 0x14, 
	0x14, 0x14, 0xF7, 0x00, 0xF7, 
	0x14, 0x14, 0x14, 0x17, 0x14, 
	0x10, 0x10, 0x1F, 0x10, 0x1F, 
	0x14, 0x14, 0x14, 0xF4, 0x14, 
	0x10, 0x10, 0xF0, 0x10, 0xF0, 
	0x00, 0x00, 0x1F, 0x10, 0x1F, 
	0x00, 0x00, 0x00, 0x1F, 0x14, 
	0x00, 0x00, 0x00, 0xFC, 0x14, 
	0x00, 0x00, 0xF0, 0x10, 0xF0, 
	0x10, 0x10, 0xFF, 0x10, 0xFF, 
	0x14, 0x14, 0x14, 0xFF, 0x14, 
	0x10, 0x10, 0x10, 0x1F, 0x00, 
	0x00, 0x00, 0x00, 0xF0, 0x10, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 
	0x38, 0x44, 0x44, 0x38, 0x44, 
	0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
	0x7E, 0x02, 0x02, 0x06, 0x06, 
	0x02, 0x7E, 0x02, 0x7E, 0x02, 
	0x63, 0x55, 0x49, 0x41, 0x63, 
	0x38, 0x44, 0x44, 0x3C, 0x04, 
	0x40, 0x7E, 0x20, 0x1E, 0x20, 
	0x06, 0x02, 0x7E, 0x02, 0x02, 
	0x99, 0xA5, 0xE7, 0xA5, 0x99, 
	0x1C, 0x2A, 0x49, 0x2A, 0x1C, 
	0x4C, 0x72, 0x01, 0x72, 0x4C, 
	0x30, 0x4A, 0x4D, 0x4D, 0x30, 
	0x30, 0x48, 0x78, 0x48, 0x30, 
	0xBC, 0x62, 0x5A, 0x46, 0x3D, 
	0x3E, 0x49, 0x49, 0x49, 0x00, 
	0x7E, 0x01, 0x01, 0x01, 0x7E, 
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 
	0x44, 0x44, 0x5F, 0x44, 0x44, 
	0x40, 0x51, 0x4A, 0x44, 0x40, 
	0x40, 0x44, 0x4A, 0x51, 0x40, 
	0x00, 0x00, 0xFF, 0x01, 0x03, 
	0xE0, 0x80, 0xFF, 0x00, 0x00, 
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00
#endif
};

const unsigned char * pFontDefaultptr = CH_Font_One;

#endif // end of font one

#ifdef CH1115_Font_Two

// ASCII font file : "THICK" Font 7 by 8 
// Define the ASCII table as Data array
// cols left to right 0x00 is  off 0xFF is all on
// Each character is 7 bits wide one byte height. 
// Each character is in a 9 by 8 bit pixel box.
// NO LOWERCASE LETTERS
static const PROGMEM  unsigned char CH_Font_Two[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  
	0x5f,0x5f,0x00,0x00,0x00,0x00,0x00, // !
	0x07,0x07,0x00,0x07,0x07,0x00,0x00, // "
	0x14,0x7f,0x7f,0x14,0x7f,0x7f,0x14, // #
	0x6f,0x6f,0x6b,0xeb,0x6b,0x7b,0x7b, // $
	0x63,0x73,0x38,0x1c,0x0e,0x67,0x63, // %
	0x7f,0x7f,0x6b,0x63,0x68,0x78,0x78, // &
	0x07,0x07,0x00,0x00,0x00,0x00,0x00, // '
	0xff,0xff,0x80,0x00,0x00,0x00,0x00, // (
	0x80,0xff,0xff,0x00,0x00,0x00,0x00, // )
	0x36,0x08,0x7f,0x7f,0x7f,0x08,0x36, // *
	0x08,0x08,0x3e,0x08,0x08,0x00,0x00, // +
	0xe0,0xe0,0x00,0x00,0x00,0x00,0x00, // ,
	0x08,0x08,0x08,0x08,0x08,0x00,0x00, // -
	0x60,0x60,0x00,0x00,0x00,0x00,0x00, // .
	0x70,0x1c,0x07,0x00,0x00,0x00,0x00, // /
	0x7f,0x7f,0x63,0x63,0x63,0x7f,0x7f, // 0
	0x60,0x66,0x66,0x7f,0x7f,0x60,0x60, // 1
	0x7b,0x7b,0x6b,0x6b,0x6b,0x6f,0x6f, // 2
	0x63,0x63,0x6b,0x6b,0x6b,0x7f,0x7f, // 3
	0x1f,0x1f,0x18,0x18,0x18,0x7e,0x7e, // 4
	0x6f,0x6f,0x6b,0x6b,0x6b,0x7b,0x7b, // 5
	0x7f,0x7f,0x6c,0x6c,0x6c,0x7c,0x7c, // 6
	0x43,0x63,0x73,0x3b,0x1f,0x0f,0x07, // 7
	0x7f,0x7f,0x6b,0x6b,0x6b,0x7f,0x7f, // 8
	0x1f,0x1f,0x1b,0x1b,0x1b,0x7f,0x7f, // 9
	0x6c,0x6c,0x00,0x00,0x00,0x00,0x00, // :
	0xec,0xec,0x00,0x00,0x00,0x00,0x00, // ;
	0x08,0x14,0x22,0x22,0x00,0x00,0x00, // <
	0x14,0x14,0x14,0x14,0x14,0x00,0x00, // =
	0x22,0x22,0x14,0x08,0x00,0x00,0x00, // >
	0x03,0x03,0x5b,0x5b,0x0b,0x0f,0x0f, // ?
	0x7f,0x7f,0x63,0x6f,0x6b,0x6f,0x6f, // @
	0x7f,0x7f,0x1b,0x1b,0x1b,0x7f,0x7f, // A
	0x7f,0x7f,0x6b,0x6b,0x6f,0x7e,0x7c, // B
	0x7f,0x7f,0x63,0x63,0x63,0x63,0x63, // C
	0x7f,0x7f,0x63,0x63,0x67,0x7e,0x7c, // D
	0x7f,0x7f,0x6b,0x6b,0x6b,0x6b,0x6b, // E
	0x7f,0x7f,0x0b,0x0b,0x0b,0x03,0x03, // F
	0x7f,0x7f,0x63,0x63,0x6b,0x7b,0x7b, // G
	0x7f,0x7f,0x18,0x18,0x18,0x7f,0x7f, // H
	0x63,0x63,0x7f,0x7f,0x63,0x63,0x63, // I
	0x60,0x60,0x60,0x60,0x60,0x7f,0x3f, // J
	0x7f,0x7f,0x18,0x18,0x1e,0x7f,0x79, // K
	0x7f,0x7f,0x60,0x60,0x60,0x60,0x60, // L
	0x7f,0x7f,0x03,0x06,0x03,0x7f,0x7f, // M
	0x7f,0x7f,0x0e,0x1c,0x38,0x7f,0x7f, // N
	0x7f,0x7f,0x63,0x63,0x63,0x7f,0x7f, // O
	0x7f,0x7f,0x1b,0x1b,0x1b,0x1f,0x1f, // P
	0x7f,0x7f,0x63,0xf3,0xf3,0x7f,0x7f, // Q
	0x7f,0x7f,0x1b,0x3b,0x7b,0x7f,0x5f, // R
	0x6f,0x6f,0x6b,0x6b,0x6b,0x7b,0x7b, // S
	0x03,0x03,0x7f,0x7f,0x03,0x03,0x03, // T
	0x7f,0x7f,0x60,0x60,0x60,0x7f,0x7f, // U
	0x1f,0x3f,0x70,0x60,0x70,0x3f,0x1f, // V
	0x3f,0x7f,0x60,0x30,0x60,0x7f,0x3f, // W
	0x77,0x7f,0x1c,0x08,0x1c,0x7f,0x77, // X
	0x07,0x0f,0x7c,0x78,0x7c,0x0f,0x07, // Y
	0x73,0x7b,0x6b,0x6b,0x6b,0x6f,0x67, // Z
};

const unsigned char * pFontThickptr = CH_Font_Two;
#endif //font Two


#ifdef CH1115_Font_Three

// ASCII font file : "Seven Segment" 4 by 8 
// Define the ASCII table as Data array
// cols left to right 0x00 is  off 0xFF is all on
// Each character is four buts wide one byte height. 
// Each character is in a 6 by 8 pixel box 

static const PROGMEM  unsigned char CH_Font_Three[] = {
	0x00,0x00,0x00,0x00, //  
	0x00,0x00,0x36,0x00, // !
	0x06,0x00,0x00,0x06, // "
	0x36,0x49,0x49,0x36, // #
	0x06,0x49,0x49,0x30, // $
	0x36,0x49,0x49,0x36, // %
	0x36,0x49,0x49,0x36, // &
	0x00,0x06,0x00,0x00, // '
	0x36,0x41,0x41,0x00, // (
	0x41,0x41,0x36,0x00, // )
	0x06,0x09,0x09,0x06, // *
	0x36,0x08,0x08,0x00, // +
	0x00,0x30,0x00,0x00, // ,
	0x08,0x08,0x00,0x00, // -
	0x00,0x30,0x00,0x00, // .
	0x30,0x08,0x08,0x06, // /
	0x36,0x41,0x41,0x36, // 0
	0x00,0x36,0x00,0x00, // 1
	0x30,0x49,0x49,0x06, // 2
	0x49,0x49,0x36,0x00, // 3
	0x06,0x08,0x08,0x36, // 4
	0x06,0x49,0x49,0x30, // 5
	0x36,0x49,0x49,0x30, // 6
	0x01,0x01,0x36,0x00, // 7
	0x36,0x49,0x49,0x36, // 8
	0x06,0x49,0x49,0x36, // 9
	0x00,0x36,0x00,0x00, // :
	0x00,0x36,0x00,0x00, // ;
	0x36,0x41,0x41,0x00, // <
	0x48,0x48,0x00,0x00, // =
	0x41,0x41,0x36,0x00, // >
	0x30,0x09,0x09,0x06, // ?
	0x36,0x49,0x49,0x36, // @
	0x36,0x09,0x09,0x36, // A
	0x36,0x49,0x49,0x36, // B
	0x36,0x41,0x41,0x00, // C
	0x30,0x48,0x48,0x36, // D
	0x36,0x49,0x49,0x00, // E
	0x36,0x09,0x09,0x00, // F
	0x36,0x49,0x49,0x30, // G
	0x36,0x08,0x08,0x36, // H
	0x00,0x36,0x00,0x00, // I
	0x40,0x40,0x36,0x00, // J
	0x36,0x08,0x08,0x36, // K
	0x36,0x40,0x40,0x00, // L
	0x36,0x01,0x01,0x36, // M
	0x36,0x01,0x01,0x36, // N
	0x36,0x41,0x41,0x36, // O
	0x36,0x09,0x09,0x06, // P
	0x06,0x09,0x09,0x36, // Q
	0x36,0x01,0x01,0x00, // R
	0x06,0x49,0x49,0x30, // S
	0x36,0x48,0x48,0x00, // T
	0x36,0x40,0x40,0x36, // U
	0x36,0x40,0x40,0x36, // V
	0x36,0x40,0x40,0x36, // W
	0x36,0x08,0x08,0x36, // X
	0x06,0x08,0x08,0x36, // Y
	0x30,0x49,0x49,0x06, // Z
	0x36,0x41,0x41,0x00, // [
	0x06,0x08,0x08,0x30, // "\"
	0x41,0x41,0x36,0x00, // ]
	0x06,0x01,0x01,0x06, // ^
	0x40,0x40,0x00,0x00, // _
	0x06,0x00,0x00,0x00, // `
	0x30,0x49,0x49,0x36, // a
	0x36,0x48,0x48,0x30, // b
	0x36,0x41,0x41,0x00, // c
	0x30,0x48,0x48,0x36, // d
	0x36,0x49,0x49,0x00, // e
	0x36,0x09,0x09,0x00, // f
	0x06,0x49,0x49,0x36, // g
	0x36,0x08,0x08,0x30, // h
	0x00,0x36,0x00,0x00, // i
	0x40,0x40,0x36,0x00, // j
	0x36,0x08,0x08,0x36, // k
	0x00,0x36,0x00,0x00, // l
	0x36,0x01,0x01,0x36, // m
	0x36,0x01,0x01,0x36, // n
	0x36,0x41,0x41,0x36, // o
	0x36,0x09,0x09,0x06, // p
	0x06,0x09,0x09,0x36, // q
	0x36,0x01,0x01,0x00, // r
	0x06,0x49,0x49,0x30, // s
	0x36,0x48,0x48,0x00, // t
	0x36,0x40,0x40,0x36, // u
	0x36,0x40,0x40,0x36, // v
	0x36,0x40,0x40,0x36, // w
	0x36,0x08,0x08,0x36, // x
	0x06,0x48,0x48,0x36, // y
	0x30,0x49,0x49,0x06, // z
};
const unsigned char * pFontSevenSegptr = CH_Font_Three;
#endif //font Three


#ifdef CH1115_Font_Four
// ASCII font file : "Wide" font 8 by 8 
// Define the ASCII table as Data array
// cols left to right 0x00 is  off 0xFF is all on
// NO LOWERCASE LETTERS

static const PROGMEM  unsigned char CH_Font_Four[]  = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //  
	0x00,0x00,0x00,0x5F,0x00,0x00,0x00,0x00, // !
	0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00, // "
	0x0a,0x1f,0x0a,0x1f,0x0a,0x00,0x00,0x00, // #
	0x24,0x2a,0x2a,0x7f,0x2a,0x2a,0x12,0x00, // $
	0x00,0x47,0x25,0x17,0x08,0x74,0x52,0x71, // %
	0x00,0x36,0x49,0x49,0x49,0x41,0x41,0x38, // &
	0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00, // '
	0x00,0x3e,0x41,0x00,0x00,0x00,0x00,0x00, // (
	0x41,0x3e,0x00,0x00,0x00,0x00,0x00,0x00, // )
	0x04,0x15,0x0e,0x15,0x04,0x00,0x00,0x00, // *
	0x08,0x08,0x3e,0x08,0x08,0x00,0x00,0x00, // +
	0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00, // ,
	0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00, // -
	0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00, // .
	0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00, // /
	0x00,0x3e,0x61,0x51,0x49,0x45,0x43,0x3e, // 0
	0x00,0x00,0x01,0x01,0x7e,0x00,0x00,0x00, // 1
	0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x46, // 2
	0x41,0x49,0x49,0x49,0x49,0x49,0x36,0x00, // 3
	0x00,0x0f,0x10,0x10,0x10,0x10,0x10,0x7f, // 4
	0x00,0x4f,0x49,0x49,0x49,0x49,0x49,0x31, // 5
	0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x30, // 6
	0x01,0x01,0x01,0x01,0x01,0x01,0x7e,0x00, // 7
	0x00,0x36,0x49,0x49,0x49,0x49,0x49,0x36, // 8
	0x00,0x06,0x49,0x49,0x49,0x49,0x49,0x3e, // 9
	0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x00, // :
	0x00,0x00,0x00,0x40,0x34,0x00,0x00,0x00, // ;
	0x08,0x14,0x22,0x00,0x00,0x00,0x00,0x00, // <
	0x14,0x14,0x14,0x14,0x14,0x00,0x00,0x00, // =
	0x22,0x14,0x08,0x00,0x00,0x00,0x00,0x00, // >
	0x00,0x06,0x01,0x01,0x59,0x09,0x09,0x06, // ?
	0x00,0x3e,0x41,0x5d,0x55,0x5d,0x51,0x5e, // @
	0x00,0x7e,0x01,0x09,0x09,0x09,0x09,0x7e, // A
	0x00,0x7f,0x41,0x49,0x49,0x49,0x49,0x36, // B
	0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x22, // C
	0x00,0x7f,0x41,0x41,0x41,0x41,0x41,0x3e, // D
	0x00,0x3e,0x49,0x49,0x49,0x49,0x49,0x41, // E
	0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x01, // F
	0x00,0x3e,0x41,0x49,0x49,0x49,0x49,0x79, // G
	0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x7f, // H
	0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00, // I
	0x00,0x38,0x40,0x40,0x41,0x41,0x41,0x3f, // J
	0x00,0x7f,0x08,0x08,0x08,0x0c,0x0a,0x71, // K
	0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x40, // L
	0x00,0x7e,0x01,0x01,0x7e,0x01,0x01,0x7e, // M
	0x00,0x7e,0x01,0x01,0x3e,0x40,0x40,0x3f, // N
	0x00,0x3e,0x41,0x41,0x41,0x41,0x41,0x3e, // O
	0x00,0x7e,0x09,0x09,0x09,0x09,0x09,0x06, // P
	0x00,0x3e,0x41,0x41,0x71,0x51,0x51,0x7e, // Q
	0x00,0x7e,0x01,0x31,0x49,0x49,0x49,0x46, // R
	0x00,0x46,0x49,0x49,0x49,0x49,0x49,0x31, // S
	0x01,0x01,0x01,0x7f,0x01,0x01,0x01,0x00, // T
	0x00,0x3f,0x40,0x40,0x40,0x40,0x40,0x3f, // U
	0x00,0x0f,0x10,0x20,0x40,0x20,0x10,0x0f, // V
	0x00,0x3f,0x40,0x40,0x3f,0x40,0x40,0x3f, // W
	0x00,0x63,0x14,0x08,0x08,0x08,0x14,0x63, // X
	0x00,0x07,0x08,0x08,0x78,0x08,0x08,0x07, // Y
	0x00,0x71,0x49,0x49,0x49,0x49,0x49,0x47, // Z
};
const unsigned char * pFontWideptr = CH_Font_Four;
#endif //font Four

#ifdef CH1115_Font_Five

// Define the ASCII table as Data array Tiny Font
// cols left to right, 0x00 is off, 0xFF is all on
// Each character is 3 bits wide one byte height. 

static const PROGMEM unsigned char CH_Font_Five[]  = {
	0x00,0x00,0x00, //  
	0x00,0x2e,0x00, // !
	0x06,0x00,0x06, // "
	0x3e,0x14,0x3e, // #
	0x0c,0x36,0x18, // $
	0x32,0x08,0x26, // %
	0x14,0x2a,0x34, // &
	0x00,0x06,0x00, // '
	0x00,0x1c,0x22, // (
	0x22,0x1c,0x00, // )
	0x14,0x08,0x14, // *
	0x08,0x1c,0x08, // +
	0x40,0x60,0x00, // ,
	0x08,0x08,0x08, // -
	0x00,0x20,0x00, // .
	0x60,0x1c,0x02, // /
	0x3e,0x22,0x3e, // 0
	0x24,0x3e,0x20, // 1
	0x32,0x2a,0x26, // 2
	0x22,0x2a,0x3e, // 3
	0x0e,0x08,0x3e, // 4
	0x2e,0x2a,0x3a, // 5
	0x3e,0x2a,0x3a, // 6
	0x02,0x3a,0x06, // 7
	0x3e,0x2a,0x3e, // 8
	0x2e,0x2a,0x3e, // 9
	0x00,0x14,0x00, // :
	0x40,0x64,0x00, // ;
	0x08,0x14,0x22, // <
	0x14,0x14,0x14, // =
	0x22,0x14,0x08, // >
	0x02,0x2a,0x06, // ?
	0x3e,0x22,0x2e, // @
	0x3e,0x0a,0x3e, // A
	0x3e,0x2a,0x36, // B
	0x3e,0x22,0x22, // C
	0x3e,0x22,0x1c, // D
	0x3e,0x2a,0x22, // E
	0x3e,0x0a,0x02, // F
	0x3e,0x22,0x3a, // G
	0x3e,0x08,0x3e, // H
	0x22,0x3e,0x22, // I
	0x30,0x20,0x3e, // J
	0x3e,0x08,0x36, // K
	0x3e,0x20,0x20, // L
	0x3e,0x04,0x3e, // M
	0x3c,0x08,0x1e, // N
	0x3e,0x22,0x3e, // O
	0x3e,0x0a,0x0e, // P
	0x3e,0x22,0x7e, // Q
	0x3e,0x0a,0x34, // R
	0x2e,0x2a,0x3a, // S
	0x02,0x3e,0x02, // T
	0x3e,0x20,0x3e, // U
	0x1e,0x20,0x1e, // V
	0x3e,0x10,0x3e, // W
	0x36,0x08,0x36, // X
	0x06,0x38,0x06, // Y
	0x32,0x2a,0x26, // Z
	0x00,0x3e,0x22, // [
	0x02,0x1c,0x60, // "\"
	0x22,0x3e,0x00, // ]
	0x04,0x02,0x04, // ^
	0x40,0x40,0x40, // _
	0x00,0x02,0x00, // `
	0x3e,0x0a,0x3e, // a
	0x3e,0x2a,0x36, // b
	0x3e,0x22,0x22, // c
	0x3e,0x22,0x1c, // d
	0x3e,0x2a,0x22, // e
	0x3e,0x0a,0x02, // f
	0x3e,0x22,0x3a, // g
	0x3e,0x08,0x3e, // h
	0x22,0x3e,0x22, // i
	0x30,0x20,0x3e, // j
	0x3e,0x08,0x36, // k
	0x3e,0x20,0x20, // l
	0x3e,0x04,0x3e, // m
	0x3c,0x08,0x1e, // n
	0x3e,0x22,0x3e, // o
	0x3e,0x0a,0x0e, // p
	0x3e,0x22,0x7e, // q
	0x3e,0x0a,0x34, // r
	0x2e,0x2a,0x3a, // s
	0x02,0x3e,0x02, // t
	0x3e,0x20,0x3e, // u
	0x1e,0x20,0x1e, // v
	0x3e,0x10,0x3e, // w
	0x36,0x08,0x36, // x
	0x06,0x38,0x06, // y
	0x32,0x2a,0x26, // z
	0x08,0x3e,0x22, // {
	0x00,0x7e,0x00, // |
	0x22,0x3e,0x08, // }
	0x02,0x06,0x04, // ~
	0x00,0x00,0x00
};

const unsigned char * pFontTinyptr = CH_Font_Five;

#endif

#ifdef CH1115_Font_Six
// ASCII font file : Homespun FONT 7 by 8 

static const PROGMEM unsigned char CH_Font_Six[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  
	0x00, 0x00, 0x00, 0x5f, 0x00, 0x00, 0x00, // !
	0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // "
	0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00, 0x00, // #
	0x6f, 0x49, 0xc9, 0x7b, 0x00, 0x00, 0x00, // $
	0x63, 0x13, 0x08, 0x64, 0x63, 0x00, 0x00, // %
	0x7f, 0xc9, 0x49, 0x63, 0x00, 0x00, 0x00, // &
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // '
	0x3e, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, // (
	0x41, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, // )
	0x0a, 0x04, 0x1f, 0x04, 0x0a, 0x00, 0x00, // *
	0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00, // +
	0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, // ,
	0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // -
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, // .
	0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, // /
	0x7f, 0x41, 0x41, 0x7f, 0x00, 0x00, 0x00, // 0
	0x01, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, // 1
	0x7b, 0x49, 0x49, 0x6f, 0x00, 0x00, 0x00, // 2
	0x63, 0x49, 0x49, 0x7f, 0x00, 0x00, 0x00, // 3
	0x0f, 0x08, 0x08, 0x7f, 0x00, 0x00, 0x00, // 4
	0x6f, 0x49, 0x49, 0x7b, 0x00, 0x00, 0x00, // 5
	0x7f, 0x49, 0x49, 0x7b, 0x00, 0x00, 0x00, // 6
	0x03, 0x01, 0x01, 0x7f, 0x00, 0x00, 0x00, // 7
	0x7f, 0x49, 0x49, 0x7f, 0x00, 0x00, 0x00, // 8
	0x0f, 0x09, 0x09, 0x7f, 0x00, 0x00, 0x00, // 9
	0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, // :
	0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, // ;
	0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, // <
	0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, // =
	0x22, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, // >
	0x03, 0x59, 0x09, 0x0f, 0x00, 0x00, 0x00, // ?
	0x7f, 0x41, 0x5d, 0x55, 0x5f, 0x00, 0x00, // @
	0x7f, 0x09, 0x09, 0x7f, 0x00, 0x00, 0x00, // A
	0x7f, 0x49, 0x49, 0x77, 0x00, 0x00, 0x00, // B
	0x7f, 0x41, 0x41, 0x63, 0x00, 0x00, 0x00, // C
	0x7f, 0x41, 0x41, 0x3e, 0x00, 0x00, 0x00, // D
	0x7f, 0x49, 0x49, 0x63, 0x00, 0x00, 0x00, // E
	0x7f, 0x09, 0x09, 0x03, 0x00, 0x00, 0x00, // F
	0x7f, 0x41, 0x49, 0x7b, 0x00, 0x00, 0x00, // G
	0x7f, 0x08, 0x08, 0x7f, 0x00, 0x00, 0x00, // H
	0x41, 0x7f, 0x41, 0x00, 0x00, 0x00, 0x00, // I
	0x60, 0x40, 0x40, 0x7f, 0x00, 0x00, 0x00, // J
	0x7f, 0x08, 0x08, 0x77, 0x00, 0x00, 0x00, // K
	0x7f, 0x40, 0x40, 0x60, 0x00, 0x00, 0x00, // L
	0x7f, 0x01, 0x01, 0x7f, 0x01, 0x01, 0x7f, // M
	0x7f, 0x01, 0x01, 0x7f, 0x00, 0x00, 0x00, // N
	0x7f, 0x41, 0x41, 0x7f, 0x00, 0x00, 0x00, // O
	0x7f, 0x09, 0x09, 0x0f, 0x00, 0x00, 0x00, // P
	0x7f, 0x41, 0xc1, 0x7f, 0x00, 0x00, 0x00, // Q
	0x7f, 0x09, 0x09, 0x77, 0x00, 0x00, 0x00, // R
	0x6f, 0x49, 0x49, 0x7b, 0x00, 0x00, 0x00, // S
	0x01, 0x01, 0x7f, 0x01, 0x01, 0x00, 0x00, // T
	0x7f, 0x40, 0x40, 0x7f, 0x00, 0x00, 0x00, // U
	0x7f, 0x20, 0x10, 0x0f, 0x00, 0x00, 0x00, // V
	0x7f, 0x40, 0x40, 0x7f, 0x40, 0x40, 0x7f, // W
	0x77, 0x08, 0x08, 0x77, 0x00, 0x00, 0x00, // X
	0x6f, 0x48, 0x48, 0x7f, 0x00, 0x00, 0x00, // Y
	0x71, 0x49, 0x49, 0x47, 0x00, 0x00, 0x00, // Z
	0x7f, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, // [
	0x03, 0x04, 0x08, 0x10, 0x60, 0x00, 0x00, // "\"
	0x41, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, // ]
	0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00, // ^
	0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, // _
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // `
	0x74, 0x54, 0x54, 0x7c, 0x00, 0x00, 0x00, // a
	0x7f, 0x44, 0x44, 0x7c, 0x00, 0x00, 0x00, // b
	0x7c, 0x44, 0x44, 0x6c, 0x00, 0x00, 0x00, // c
	0x7c, 0x44, 0x44, 0x7f, 0x00, 0x00, 0x00, // d
	0x7c, 0x54, 0x54, 0x5c, 0x00, 0x00, 0x00, // e
	0x7f, 0x05, 0x05, 0x01, 0x00, 0x00, 0x00, // f
	0xbc, 0xa4, 0xa4, 0xfc, 0x00, 0x00, 0x00, // g
	0x7f, 0x04, 0x04, 0x7c, 0x00, 0x00, 0x00, // h
	0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // i
	0x80, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, // j
	0x7f, 0x04, 0x04, 0x7a, 0x00, 0x00, 0x00, // k
	0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // l
	0x7c, 0x04, 0x04, 0x7c, 0x04, 0x04, 0x7c, // m
	0x7c, 0x04, 0x04, 0x7c, 0x00, 0x00, 0x00, // n
	0x7c, 0x44, 0x44, 0x7c, 0x00, 0x00, 0x00, // o
	0xfc, 0x44, 0x44, 0x7c, 0x00, 0x00, 0x00, // p
	0x7c, 0x44, 0x44, 0xfc, 0x00, 0x00, 0x00, // q
	0x7c, 0x04, 0x04, 0x0c, 0x00, 0x00, 0x00, // r
	0x5c, 0x54, 0x54, 0x74, 0x00, 0x00, 0x00, // s
	0x7f, 0x44, 0x44, 0x60, 0x00, 0x00, 0x00, // t
	0x7c, 0x40, 0x40, 0x7c, 0x00, 0x00, 0x00, // u
	0x7c, 0x20, 0x10, 0x0c, 0x00, 0x00, 0x00, // v
	0x7c, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x7c, // w
	0x6c, 0x10, 0x10, 0x6c, 0x00, 0x00, 0x00, // x
	0xbc, 0xa0, 0xa0, 0xfc, 0x00, 0x00, 0x00, // y
	0x64, 0x54, 0x54, 0x4c, 0x00, 0x00, 0x00, // z
	0x08, 0x3e, 0x41, 0x00, 0x00, 0x00, 0x00, // {
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // |
	0x41, 0x3e, 0x08, 0x00, 0x00, 0x00, 0x00, // }
	0x1c, 0x04, 0x1c, 0x10, 0x1c, 0x00, 0x00 // ~
};

const unsigned char * pFontHomeSpunptr = CH_Font_Six;

#endif

#ifdef CH1115_Font_Seven
// ASCII font file : "bignum" font 5 16 by 32 , 
// Define the ASCII table as Data array
// NUMBERS + ":" ONLY 
// 32 * 16/8 = 64 ,;;, 64 * 11 = 704 bytes
// 32 height 16 width
static const PROGMEM uint8_t CH_Font_Seven [11][64] = 
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,    /*"0",0*/
	0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x0C,
	0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x0C,0x30,0x00,0x00,0x0C,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   /*"1",1*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x01,0xFF,0xFC,0x3C,0x01,0xFF,0xFC,   /*"2",2*/
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x3F,0xFF,0x80,0x0C,0x3F,0xFF,0x80,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x3C,0x38,0x00,0x00,0x3C,   /*"3",3*/
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x80,0x00,0x3F,0xFF,0x80,0x00,  /*"4",4*/
	0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,
	0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x80,0x3C,0x3F,0xFF,0x80,0x3C,  /*"5",5*/
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0xFF,0xFC,0x30,0x01,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,  /*"6",6*/
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x3C,0x01,0xFF,0xFC,0x3C,0x01,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,  /*"7",7*/
	0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,
	0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x00,0x00,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},    

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,  /*"8",8*/
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x80,0x3C,0x3F,0xFF,0x80,0x3C,  /*"9",9*/
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,0x30,0x01,0x80,0x0C,
	0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  /*":",10*/
	0x00,0x00,0x00,0x00,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0C,0x00,0x00,0x30,
	0x0C,0x00,0x00,0x30,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};  
  
const uint8_t (* pFontBigNumptr)[64] = CH_Font_Seven;
#endif // Font 7

#ifdef CH1115_Font_Eight

// "medNums" font 16 height 16 width 
// Define the ASCII table as Data array
// NUMBERS + ":" ONLY 
static const  PROGMEM uint8_t CH_Font_Eight[11][32] = 
{
	{0x00,0x00,0x3F,0xFC,0x3F,0xFC,0x30,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
	0x30,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,0x3F,0xFC,0x3F,0xFC,0x00,0x00},/*"0",0*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,
	0x30,0x00,0x3F,0xFC,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"1",1*/
	{0x00,0x00,0x39,0xFC,0x39,0xFC,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,
	0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x3F,0x8C,0x3F,0x8C,0x00,0x00},/*"2",2*/
	{0x00,0x00,0x38,0x1C,0x38,0x1C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,
	0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x3F,0xFC,0x3F,0xFC,0x00,0x00},/*"3",3*/
	{0x00,0x00,0x3F,0x80,0x3F,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x3F,0xFC,0x3F,0xFC,0x00,0x00},/*"4",4*/
	{0x00,0x00,0x3F,0x8C,0x3F,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,
	0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0xFC,0x31,0xFC,0x00,0x00},/*"5",5*/
	{0x00,0x00,0x3F,0xFC,0x3F,0xFC,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,
	0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0xFC,0x31,0xFC,0x00,0x00},/*"6",6*/
	{0x00,0x00,0x38,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,
	0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3F,0xFC,0x3F,0xFC,0x00,0x00},/*"7",7*/
	{0x00,0x00,0x3F,0xFC,0x3F,0xFC,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,
	0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x3F,0xFC,0x3F,0xFC,0x00,0x00},/*"8",8*/
	{0x00,0x00,0x3F,0x9C,0x3F,0x9C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,
	0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x31,0x8C,0x3F,0xFC,0x3F,0xFC,0x00,0x00},/*"9",9*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x30,
	0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*":",10*/
};

const uint8_t (* pFontMedNumptr)[32] = CH_Font_Eight;
#endif
