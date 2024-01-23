 /*!
	@file ER_OLEDM1_CH1115_graphics.hpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller header file
	for the graphics  based functions.   Project Name: ER_OLEDM1_CH1115
	 URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@author  Gavin Lyons
*/

#ifndef _ER_OLEDM1_CH1115_GRAPHICS_H
#define _ER_OLEDM1_CH1115_GRAPHICS_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#define CH1115_Swap(a, b) { int16_t t = a; a = b; b = t; }

/*! CH1115 Enum to define return codes from some text and bitmap functions  */
enum CH1115_Return_Codes_e : uint8_t
{
	CH1115_Success = 0,                /**< Success!  */
	CH1115_WrongFont = 2,              /**< Wrong Font selected for this method , There are two families of font included with different overloaded functions*/
	CH1115_CharScreenBounds = 3,       /**< Text Character is out of Screen bounds, Check x and y*/
	CH1115_CharFontASCIIRange = 4,     /**< Text Character is outside of chosen Fonts ASCII range, Check the selected Fonts ASCII range.*/
	CH1115_CharArrayNullptr = 5,       /**< Text Character Array is an invalid pointer object */
	CH1115_BitmapNullptr = 7,          /**< The Bitmap data array is an invalid pointer object */
	CH1115_BitmapScreenBounds = 8,     /**< The bitmap starting point is outside screen bounds check x and y */
	CH1115_BitmapLargerThanScreen = 9, /**< The Bitmap is larger than screen , check  w and h*/
	CH1115_BitmapVerticalSize = 10,    /**< A vertical  Bitmap's height must be divisible by 8. */
	CH1115_BitmapHorizontalSize = 11,  /**< A horizontal Bitmap's width  must be divisible by 8  */
};

/*! OLED rotate modes in degrees, Note this is separate from OLED command method for rotation. */
enum  CH1115_rotate_e : uint8_t
{
	CH1115_Degrees_0 = 0, /**< No rotation 0 degrees*/
	CH1115_Degrees_90,    /**< Rotation 90 degrees*/
	CH1115_Degrees_180,   /**< Rotation 180 degrees*/
	CH1115_Degrees_270   /**< Rotation 270 degrees*/
};

/*! Oled fonts  enum types*/
enum CH1115_Font_Type_e  : uint8_t
{
	CH1115Font_Default = 1,    /**< Default Font, Full extended ASCII */
	CH1115Font_Thick = 2,      /**< Thick font , no lower case letters*/
	CH1115Font_Seven_Seg = 3,  /**< Seven Segment Font */
	CH1115Font_Wide = 4,       /**< Wide font no lowercase letters*/
	CH1115Font_Tiny = 5,       /**< Tiny font */
	CH1115Font_Homespun = 6,   /**< Homespun Font */
	CH1115Font_Bignum = 7,     /**< Bignum numbers only */
	CH1115Font_Mednum = 8,      /**< Mednum number only */
	CH1115Font_ArialRound = 9,  /**< Arial round font */
	CH1115Font_ArialBold = 10,  /**< Arial bold font */
	CH1115Font_Mia = 11,        /**< Mia font */
	CH1115Font_Dedica = 12       /**< dedica font */
};

/*! @brief Graphics class to hold graphic related functions */
class ERMCH1115_graphics : public Print {

public:

/*! CH1115 Enum to define current font type selected  */

	ERMCH1115_graphics(int16_t w, int16_t h);

	// implemented in the subclass:
	virtual void drawPixel(int16_t x, int16_t y, uint8_t color) = 0;
	// Shape related
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	void fillScreen(uint8_t color);
	void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
	void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
		uint8_t color);
	void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
	void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
		int16_t delta, uint8_t color);
	void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint8_t color);
	void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint8_t color);
	void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint8_t color);
	void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		int16_t radius, uint8_t color);

	// Bitmap related
	CH1115_Return_Codes_e drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
			int16_t w, int16_t h, uint8_t color, uint8_t bg);
	void	setDrawBitmapAddr(boolean mode);

	// Text related
	void setCursor(int16_t x, int16_t y);
	void setTextColor(uint8_t c);
	void setTextColor(uint8_t c, uint8_t bg);
	void setTextSize(uint8_t s);
	void setTextWrap(boolean w);

	void setFontNum(CH1115_Font_Type_e FontNumber);
	CH1115_Return_Codes_e drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color , uint8_t bg);
	CH1115_Return_Codes_e drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg);
	CH1115_Return_Codes_e drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t s);
	CH1115_Return_Codes_e drawText(uint8_t x, uint8_t y, char *pTxt, uint8_t c, uint8_t bg, uint8_t s);

#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void   write(uint8_t);
#endif

	// Screen related
	void setRotation(CH1115_rotate_e );
	CH1115_rotate_e getRotation(void);
	int16_t height(void) const;
	int16_t width(void) const;

protected:
	const int16_t WIDTH;    /**< This is the 'raw' display w - never changes */
	const int16_t HEIGHT;   /**< This is the 'raw' display h - never changes*/
	int16_t _width;               /**< Display w as modified by current rotation*/
	int16_t  _height;             /**< Display h as modified by current rotation*/
	int16_t  _cursorX=0;           /**< Current X co-ord cursor position */
	int16_t _cursorY=0;            /**< Current Y co-ord cursor position */
	CH1115_rotate_e  _OLED_rotate = CH1115_Degrees_0; /**< Enum to hold rotation */

	uint8_t _textColor = 0x00;             /**< Text foreground color */
	uint8_t _textBgColor = 0x01;        /**< Text background color */
	uint8_t _textSize=1;              /**< Size of text ,fonts 1-6 */
	boolean _textWrap=true;              /**< If set, Wrap text at right edge of display*/

	boolean _drawBitmapAddr= true; /**< data addressing mode for method drawBitmap, True-vertical , false-horizontal */

private:

	/*! Width of the font in bits each representing a bytes sized column*/
	enum OLED_Font_width_e : uint8_t
	{
		CH1115Font_width_3 = 3,   /**< 3 tiny font */
		CH1115Font_width_4 = 4,   /**< 4 seven segment font */
		CH1115Font_width_5 = 5,   /**< 5 default font */
		CH1115Font_width_6 = 6,   /**< 12 dedica font  */
		CH1115Font_width_7 = 7,   /**< 6 homespun & 2 thick font*/
		CH1115Font_width_8 = 8,   /**< 8 wide & mia font*/
		CH1115Font_width_16  = 16 /**< 16 font 7-10*/
	};

	/*! font offset in the ASCII table*/
	enum OLED_Font_offset_e : uint8_t
	{
		CH1115Font_offset_none = 0x00,  /**< Full extended ASCII */
		CH1115Font_offset_space = 0x20, /**< Starts at Space, alphanumeric */
		CH1115Font_offset_minus = 0x2D, /**< Starts at Minus, extended numeric */
		CH1115Font_offset_zero = 0x30   /**< Starts at zero, numeric */
	};

	/*! Height of the font in bits*/
	enum OLED_Font_height_e : uint8_t
	{
		CH1115Font_height_8 = 8,  /**< 8 bit font 1-6 at size 1*/
		CH1115Font_height_12 = 12, /**< 12 bit font 12 */
		CH1115Font_height_16 = 16, /**< 16 bit font 8, 10 11*/
		CH1115Font_height_24 = 24, /**< 24 bit font 9 */
		CH1115Font_height_32 = 32  /**< 32 bit font 7 */
	};

	/*! Number of ASCII characters in Font */
	enum OLED_Font_Length_e : uint8_t
	{
		CH1115FontLenNumeric = 14,         /**< extended Numeric 0x2D - 0x3A */
		CH1115FontLenAlphaNumNoLCase = 59, /**< reduced Alphanumeric 0x20-0x5A*/
		CH1115FontLenAlphaNum = 95,        /**< Full Alphanumeric 0x20-0x7E */
		CH1115FontLenHalf= 128,           /**< half Range  0-127*/
		CH1115FontLenAll = 255           /**< Full Range  0-0xFF */
	};

	uint8_t _FontNumber = 1;           /**< Store current font */
	uint8_t _CurrentFontWidth =5;      /**< Store current font width */
	uint8_t _CurrentFontoffset = 0;   /**< Store current offset width */
	uint8_t _CurrentFontheight = 8;   /**< Store current offset height */
	uint8_t _CurrentFontLength = 128; /**<Store current font number of characters */
};

#endif
