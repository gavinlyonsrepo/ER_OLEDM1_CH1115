/*
* Project Name: ER_OLEDM1_CH1115
* File: ER_OLEDM1_CH1115_graphics.hpp
* Description: ER_OLEDM1 OLED driven by CH1115controller header file for the graphics functions based 
* URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
*/

#ifndef _ER_OLEDM1_CH1115_GRAPHICS_H
#define _ER_OLEDM1_CH1115_GRAPHICS_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#define swap(a, b) { int16_t t = a; a = b; b = t; }

typedef enum 
{
    OLEDFontType_Default = 1,
    OLEDFontType_Thick = 2, // NO LOWERCASE
    OLEDFontType_SevenSeg = 3,
    OLEDFontType_Wide = 4, // NO LOWERCASE
    OLEDFontType_Tiny = 5,
    OLEDFontType_Homespun = 6,
    OLEDFontType_Bignum = 7, // NUMBERS + : . ,one size
    OLEDFontType_Mednum = 8   // NUMBERS + : . ,one size
}OLEDFontType_e;

typedef enum 
{
	OLEDFontWidth_3 = 3,
	OLEDFontWidth_5 = 5, 
	OLEDFontWidth_7 = 7, 
	OLEDFontWidth_4 = 4, 
	OLEDFontWidth_8 = 8,
	OLEDFontWidth_16 = 16
}OLEDFontWidth_e; // width of the font in bytes cols.

typedef enum 
{
	OLEDFontOffset_Extend = 0x00, //   extends ASCII
	OLEDFontOffset_Space = 0x20,  // Starts at Space
	OLEDFontOffset_Number = 0x30,  // Starts at number '0'
}OLEDFontOffset_e; // font offset in the ASCII table

typedef enum 
{
	OLEDFontHeight_8 = 8, 
	OLEDFontHeight_16 = 16, 
	OLEDFontHeight_32 = 32
}OLEDFontHeight_e; // height of the font in bits

class ERMCH1115_graphics : public Print {

 public:

	ERMCH1115_graphics(int16_t w, int16_t h); // Constructor

#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void   write(uint8_t);
#endif
	// Defined by the subclass:
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
	const int16_t WIDTH;
	const int16_t HEIGHT;   // This is the 'raw' display w/h - never changes
	int16_t _width; 
	int16_t  _height; // Display w/h as modified by current rotation
	int16_t  cursor_x; 
	int16_t  cursor_y;
	
	uint8_t textcolor;
	uint8_t textbgcolor;
	uint8_t textsize;
	
	uint8_t rotation;
	boolean wrap; // If set, 'wrap' text at right edge of display
	boolean drawBitmapAddr; // True = vertical , false = horizontal
	
	uint8_t _FontNumber = 1;
	uint8_t _CurrentFontWidth = 5;
	uint8_t _CurrentFontoffset = 0x00;
	uint8_t _CurrentFontheight = 8;
};

#endif 
