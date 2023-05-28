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

/*! @brief Graphics class to hold graphic related functions */
class ERMCH1115_graphics : public Print {

public:

	/*! Enum to define current font type selected  */ 
	enum OLEDFontType_e : uint8_t
	{
		OLEDFontType_Default = 1,      /**<  (1) default  (FUll ASCII with mods) */
		OLEDFontType_Thick = 2,         /**<  (2) thick (NO LOWERCASE) */
		OLEDFontType_SevenSeg = 3,  /**<  (3) seven segment  */
		OLEDFontType_Wide = 4,          /**<  (4) wide (NO LOWERCASE) */
		OLEDFontType_Tiny = 5,            /**<  (5) tiny */
		OLEDFontType_Homespun = 6,  /**<  (6) HomeSpun */
		OLEDFontType_Bignum = 7,      /**< (7) big numbers  NUMBERS only + : . ,fixed size */
		OLEDFontType_Mednum = 8     /**< (8) Med numbers NUMBERS + : . , fixed size */
	};
 
	ERMCH1115_graphics(int16_t w, int16_t h); 

#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void   write(uint8_t);
#endif
	// implemented in the subclass:
	virtual void drawPixel(int16_t x, int16_t y, uint8_t color) = 0;

	virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
	virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
	virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
	virtual void fillScreen(uint8_t color);

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
	void	drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
			int16_t w, int16_t h, uint8_t color, uint8_t bg);

	void setCursor(int16_t x, int16_t y);
	void setTextColor(uint8_t c);
	void setTextColor(uint8_t c, uint8_t bg);
	void setTextSize(uint8_t s);
	void setTextWrap(boolean w);
	void setRotation(uint8_t r);
	void	setDrawBitmapAddr(boolean mode);
	uint8_t getRotation(void) const;

	int16_t height(void) const;
	int16_t width(void) const;
	
	void setFontNum(OLEDFontType_e  FontNumber);
	void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color,
		uint8_t bg, uint8_t size);
	void drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg, uint8_t size);
	void drawCharNum(uint8_t x, uint8_t y, uint8_t c, uint8_t color , uint8_t bg);
	void drawTextNum(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg);
	
protected:
	const int16_t WIDTH;    /**< This is the 'raw' display w - never changes */
	const int16_t HEIGHT;   /**< This is the 'raw' display h - never changes*/
	int16_t _width;               /**< Display w as modified by current rotation*/
	int16_t  _height;             /**< Display h as modified by current rotation*/
	int16_t  cursor_x;           /**< Current X co-ord cursor position */
	int16_t  cursor_y;            /**< Current Y co-ord cursor position */
	
	uint8_t textcolor;             /**< Text foreground color */
	uint8_t textbgcolor;        /**< Text background color */
	uint8_t textsize;              /**< Size of text ,fonts 1-6 */
	 
	uint8_t rotation;                /**< Rotation of screen 0-3 */
	boolean wrap;                    /**< If set, 'wrap' text at right edge of display*/
	boolean drawBitmapAddr; /**< data addressing mode for method drawBitmap, True-vertical , false-horizontal */
	
	uint8_t _FontNumber = 1;                /**< Holds current font number */
	uint8_t _CurrentFontWidth = 5;        /**<Holds current font width in bits */
	uint8_t _CurrentFontoffset = 0x00;  /**<Holds current font ASCII table offset */
	uint8_t _CurrentFontheight = 8;      /**<Holds current font height in bits */
	
private:
	
	/*!  Width of the font in bits .*/
	enum OLEDFontWidth_e : uint8_t
	{
		OLEDFontWidth_3 = 3,    /**< 3 tiny font */
		OLEDFontWidth_4 = 4,    /**< 4 seven segment font */
		OLEDFontWidth_5 = 5,    /**< 5 default font */
		OLEDFontWidth_7 = 7,    /**< 7 homespun & thick font*/
		OLEDFontWidth_8 = 8,    /**< 8 wide font */
		OLEDFontWidth_16 = 16 /**< Big and Medium number  font */
	}; 
	
	/*! font offset in the ASCII table */
	enum OLEDFontOffset_e 
	{
		OLEDFontOffset_Extend = 0x00,     /**<   extends ASCII */
		OLEDFontOffset_Space = 0x20,      /**< Starts at Space  */
		OLEDFontOffset_Number = 0x30   /**<  Starts at number '0' */
	}; 
	
	/*! height of the font in bits */
	enum OLEDFontHeight_e : uint8_t
	{
		OLEDFontHeight_8 = 8,       /**< 8 font  1-6 at size 1*/
		OLEDFontHeight_16 = 16,   /**< 16 font 8 */
		OLEDFontHeight_32 = 32    /**< 32 font 7 */
	}; 
};

#endif 
