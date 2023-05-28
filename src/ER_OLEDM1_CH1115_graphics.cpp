 /*!
	@file ER_OLEDM1_CH1115_graphics.cpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller source file
	for the graphics  based functions.   Project Name: ER_OLEDM1_CH1115
	@author  Gavin Lyons
*/

#include "ER_OLEDM1_CH1115_graphics.hpp"
#include "ER_OLEDM1_CH1115_font.hpp"
#include "ER_OLEDM1_CH1115.hpp"

#ifdef __AVR__
 #include <avr/pgmspace.h>
#else
#ifndef  ESP8266
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif
#endif

/*!
	@brief init the OLED Graphics class object
	@param w width defined  in sub-class
	@param h height defined in sub-class
 */
ERMCH1115_graphics::ERMCH1115_graphics(int16_t w, int16_t h):
	WIDTH(w), HEIGHT(h)
{
	_width    = WIDTH;
	_height   = HEIGHT;
	rotation  = 0;
	cursor_y  = cursor_x    = 0;
	textsize  = 1;
	textcolor = 0x00;
	textbgcolor = 0xFF;
	wrap      = true;
	drawBitmapAddr=true;
}

/*!
	@brief draws a circle where (x0,y0) are center coordinates an r is circle radius.
	@param x0 circle center x position
	@param y0 circle center y position
	@param r radius of circle
	@param color The color of the circle
*/
void ERMCH1115_graphics::drawCircle(int16_t x0, int16_t y0, int16_t r,
	uint8_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	drawPixel(x0  , y0+r, color);
	drawPixel(x0  , y0-r, color);
	drawPixel(x0+r, y0  , color);
	drawPixel(x0-r, y0  , color);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
	
		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);
	}
}

/*!
	@brief Used internally by drawRoundRect
*/
void ERMCH1115_graphics::drawCircleHelper( int16_t x0, int16_t y0,
							 int16_t r, uint8_t cornername, uint8_t color) {
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & 0x4) {
			drawPixel(x0 + x, y0 + y, color);
			drawPixel(x0 + y, y0 + x, color);
		} 
		if (cornername & 0x2) {
			drawPixel(x0 + x, y0 - y, color);
			drawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			drawPixel(x0 - y, y0 + x, color);
			drawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			drawPixel(x0 - y, y0 - x, color);
			drawPixel(x0 - x, y0 - y, color);
		}
	}
}

/*!
	@brief fills a circle where (x0,y0) are center coordinates an r is circle radius.
	@param x0 circle center x position
	@param y0 circle center y position
	@param r radius of circle
	@param color color of the circle 
*/
void ERMCH1115_graphics::fillCircle(int16_t x0, int16_t y0, int16_t r,
									uint8_t color) {
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}

/*!
	@brief Used internally by fill circle fillRoundRect and fillcircle
*/
void ERMCH1115_graphics::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
		uint8_t cornername, int16_t delta, uint8_t color) {

	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1) {
			drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}

/*!
	@brief draws a line from (x0,y0) to (x1,y1).
	@param x0 x start coordinate
	@param y0 y start coordinate
	@param x1 x end coordinate
	@param y1 y end coordinate
	@param color color to draw line
*/
void ERMCH1115_graphics::drawLine(int16_t x0, int16_t y0,
								int16_t x1, int16_t y1,
								uint8_t color) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		CH1115_Swap(x0, y0);
		CH1115_Swap(x1, y1);
	}

	if (x0 > x1) {
		CH1115_Swap(x0, x1);
		CH1115_Swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			drawPixel(y0, x0, color);
		} else {
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

/*!
	@brief draws rectangle at (x,y) where h is height and w is width of the rectangle.
	@param x x start coordinate
	@param y y start coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param color color to draw  rect
*/
void ERMCH1115_graphics::drawRect(int16_t x, int16_t y,
								int16_t w, int16_t h,
								uint8_t color) {
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}

/*!
	@brief Draws a vertical line starting at (x,y) with height h.
	@param x The starting x coordinate
	@param y The starting y coordinate
	@param h The height of the line
	@param color The color of the line
*/
void ERMCH1115_graphics::drawFastVLine(int16_t x, int16_t y,
								 int16_t h, uint8_t color) {
	// Update in subclasses if desired!
	drawLine(x, y, x, y+h-1, color);
}

/*!
	@brief Draws a horizontal line starting at (x,y) with width w.
	@param x The starting x coordinate
	@param y The starting y coordinate
	@param w The width of the line
	@param color The color of the line 
*/
void ERMCH1115_graphics::drawFastHLine(int16_t x, int16_t y,
								 int16_t w, uint8_t color) {
	// Update in subclasses if desired!
	drawLine(x, y, x+w-1, y, color);
}

/*!
	@brief fills a rectangle starting from coordinates (x,y) with width of w and height of h.
	@param x x coordinate
	@param y y coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param color color to fill  rectangle 
*/
void ERMCH1115_graphics::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
								uint8_t color) {
	// Update in subclasses if desired!
	for (int16_t i=x; i<x+w; i++) {
		drawFastVLine(i, y, h, color);
	}
}

/*!
	@brief Fills the whole screen with a given color.
	@param  color color to fill screen
*/
void ERMCH1115_graphics::fillScreen(uint8_t color) {
	fillRect(0, 0, _width, _height, color);
}

/*!
	@brief draws a rectangle with rounded edges
	@param x x start coordinate
	@param y y start coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param r radius of the rounded edges
	@param color color to draw rectangle 
*/
void ERMCH1115_graphics::drawRoundRect(int16_t x, int16_t y, int16_t w,
	int16_t h, int16_t r, uint8_t color) {
	drawFastHLine(x+r  , y    , w-2*r, color); // Top
	drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	drawFastVLine(x    , y+r  , h-2*r, color); // Left
	drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	drawCircleHelper(x+r    , y+r    , r, 1, color);
	drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

/*!
	@brief Fills a rectangle with rounded edges
	@param x x start coordinate
	@param y y start coordinate
	@param w width of the rectangle
	@param h height of the rectangle
	@param r  radius of the rounded edges
	@param color color to fill round  rectangle 
*/
void ERMCH1115_graphics::fillRoundRect(int16_t x, int16_t y, int16_t w,
								 int16_t h, int16_t r, uint8_t color) {
	// smarter version
	fillRect(x+r, y, w-2*r, h, color);

	// draw four corners
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

/*!
	@brief draws a triangle of coordinates (x0,y0), (x1,y1) and (x2,y2).
	@param x0 x start coordinate point 1
	@param y0 y start coordinate point 1
	@param x1 x start coordinate point 2
	@param y1 y start coordinate point 2
	@param x2 x start coordinate point 3
	@param y2 y start coordinate point 3
	@param color color to draw triangle 
*/
void ERMCH1115_graphics::drawTriangle(int16_t x0, int16_t y0,
								int16_t x1, int16_t y1,
								int16_t x2, int16_t y2, uint8_t color) {
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}

/*!
	@brief Fills a triangle of coordinates (x0,y0), (x1,y1) and (x2,y2).
	@param x0 x start coordinate point 1
	@param y0 y start coordinate point 1
	@param x1 x start coordinate point 2
	@param y1 y start coordinate point 2
	@param x2 x start coordinate point 3
	@param y2 y start coordinate point 3
	@param color color to fill  triangle
*/
void ERMCH1115_graphics::fillTriangle ( int16_t x0, int16_t y0,
									int16_t x1, int16_t y1,
									int16_t x2, int16_t y2, uint8_t color) {

	int16_t a, b, y, last;

	if (y0 > y1) {
		CH1115_Swap(y0, y1); CH1115_Swap(x0, x1);
	}
	if (y1 > y2) {
		CH1115_Swap(y2, y1); CH1115_Swap(x2, x1);
	}
	if (y0 > y1) {
		CH1115_Swap(y0, y1); CH1115_Swap(x0, x1);
	}

	if(y0 == y2) { 
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		drawFastHLine(a, y0, b-a+1, color);
		return;
	}

	int16_t
		dx01 = x1 - x0,
		dy01 = y1 - y0,
		dx02 = x2 - x0,
		dy02 = y2 - y0,
		dx12 = x2 - x1,
		dy12 = y2 - y1;
	int32_t
		sa   = 0,
		sb   = 0;

	if(y1 == y2) last = y1;   
	else         last = y1-1; 

	for(y=y0; y<=last; y++) {
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;

		if(a > b) CH1115_Swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}

	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;

		if(a > b) CH1115_Swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}
}

/*!
	@brief Draw a 1-bit color bitmap 
	@param x x co-ord position
	@param y y co-ord posiiton a
	@param bitmap pointer to bitmap data (must be PROGMEM memory) 
	@param w width of the bitmap 
	@param h height of the bitmap 
	@param color foreground colour 
	@param bg background colour.
	@note Variable drawBitmapAddr controls data addressing
		-# drawBitmapAddr  = true Vertical  data addressing
		-# drawBitmapAddr  = false Horizontal data addressing
*/
void ERMCH1115_graphics::drawBitmap(int16_t x, int16_t y,
						const uint8_t *bitmap, int16_t w, int16_t h,
						uint8_t color, uint8_t bg) {
							
if (drawBitmapAddr== true)
{
// Vertical byte bitmaps mode 
	uint8_t vline;
	int16_t i, j, r = 0, yin = y;
	
	for (i=0; i<(w+1); i++ ) {
		if (r == (h+7)/8 * w) break;
		vline = pgm_read_byte(bitmap + r );
		r++;
		if (i == w) {
			y = y+8;
			i = 0;
		}
		
		for (j=0; j<8; j++ ) {
			if (y+j-yin == h) break;
			if (vline & 0x1) {
				drawPixel(x+i, y+j, color);
			}
			else {
				drawPixel(x+i, y+j, bg);
			}	
			vline >>= 1;
		}
	}
} else if (drawBitmapAddr == false) {
// Horizontal byte bitmaps mode 
	int16_t byteWidth = (w + 7) / 8;
	uint8_t byte = 0;
	for (int16_t j = 0; j < h; j++, y++) 
	{
		for (int16_t i = 0; i < w; i++) 
		{
			if (i & 7)
				byte <<= 1;
			else
				byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
			drawPixel(x+i, y, (byte & 0x80) ? color : bg);
		}
	}

} // end of elseif
}

/*!
	@brief: called by the print class after it converts the data to a character
	@param c character
*/
#if ARDUINO >= 100
size_t ERMCH1115_graphics::write(uint8_t c) {
#else
void ERMCH1115_graphics::write(uint8_t c) {
#endif

	if (_FontNumber < OLEDFontType_Bignum) // fonts 1-6
	{
		if (c == '\n') 
		{
			cursor_y += textsize*_CurrentFontheight;
			cursor_x  = 0;
		} else if (c == '\r') 
		{
			// Skip 
		} else 
		{
			drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
			cursor_x += textsize*(_CurrentFontWidth+1);
			if (wrap && (cursor_x > (_width - textsize*(_CurrentFontWidth+1)))) 
			{
				cursor_y += textsize*_CurrentFontheight;
				cursor_x = 0;
			}
		}
		
	}else if (_FontNumber >= OLEDFontType_Bignum) // fonts 7-8
	{
		uint8_t radius = 3;
		if (_FontNumber == OLEDFontType_Mednum) radius = 2;
		
		if (c == '\n') 
		{
			cursor_y += _CurrentFontheight;
			cursor_x  = 0;
		} else if (c == '\r') 
		{
			// Skip
		} else if (c == '.')
		{
			// draw a circle for decimal point skip a space.
			fillCircle(cursor_x+(_CurrentFontWidth/2), cursor_y + (_CurrentFontheight-8), radius, textcolor);
			cursor_x += (_CurrentFontWidth+1);
			if (wrap && (cursor_x  > (_width - (_CurrentFontWidth+1)))) 
			{
				cursor_y += _CurrentFontheight;
				cursor_x = 0;
			}
		}else 
		{
			drawCharNum(cursor_x, cursor_y, c, textcolor, textbgcolor);
			cursor_x += (_CurrentFontWidth+1);
			if (wrap && (cursor_x > (_width - (_CurrentFontWidth+1)))) 
			{
				cursor_y += _CurrentFontheight;
				cursor_x = 0;
			}
		}
	}

#if ARDUINO >= 100
	return 1;
#endif
}

/*!
	@brief  writes a char (c) on the OLED
	@param  x X coordinate
	@param  y Y coordinate
	@param  c The ASCII character
	@param color  color
	@param bg background color
	@param size 1-x
	@note for font #1-6 only
*/
void ERMCH1115_graphics::drawChar(int16_t x, int16_t y, unsigned char c,
								uint8_t color, uint8_t bg, uint8_t size) {

	if((x >= _width)            || // Clip right
		 (y >= _height)           || // Clip bottom
		 ((x + (_CurrentFontWidth+1) * size - 1) < 0) || // Clip left
		 ((y + _CurrentFontheight * size - 1) < 0))   // Clip top
		return;

	for (int8_t i=0; i<(_CurrentFontWidth+1); i++ ) {
		uint8_t line;
		if (i == _CurrentFontWidth)
		{ 
			line = 0x0;
		}
		else 
		{
			 switch (_FontNumber) {
#ifdef CH1115_Font_One
				case OLEDFontType_Default : line = pgm_read_byte(pFontDefaultptr + ((c - _CurrentFontoffset) * _CurrentFontWidth) + i); break;
#endif 
#ifdef CH1115_Font_Two
						case OLEDFontType_Thick : line = pgm_read_byte(pFontThickptr+ ((c - _CurrentFontoffset) * _CurrentFontWidth) + i); break;
#endif
#ifdef CH1115_Font_Three
						case OLEDFontType_SevenSeg: line = pgm_read_byte(pFontSevenSegptr + ((c - _CurrentFontoffset) * _CurrentFontWidth) + i); break;
#endif
#ifdef CH1115_Font_Four
						case OLEDFontType_Wide : line = pgm_read_byte(pFontWideptr + ((c - _CurrentFontoffset) * _CurrentFontWidth) + i); break;
#endif
#ifdef CH1115_Font_Five
						case OLEDFontType_Tiny : line = pgm_read_byte(pFontTinyptr + ((c - _CurrentFontoffset) * _CurrentFontWidth) + i); break;
#endif
#ifdef CH1115_Font_Six
						case OLEDFontType_Homespun : line = pgm_read_byte(pFontHomeSpunptr + ((c - _CurrentFontoffset) * _CurrentFontWidth) + i); break;
#endif
						default: // wrong font number
								return;
						break;
				}
		}
		for (int8_t j = 0; j<_CurrentFontheight; j++) {
			if (line & 0x1) {
				if (size == 1) // default size
					drawPixel(x+i, y+j, color);
				else {  // big size
					fillRect(x+(i*size), y+(j*size), size, size, color);
				} 
			} else if (bg != color) {
				if (size == 1) // default size
					drawPixel(x+i, y+j, bg);
				else {  // big size
					fillRect(x+i*size, y+j*size, size, size, bg);
				}
			}
			line >>= 1;
		}
	}
}

/*! 
	@brief set the cursor position  
	@param x X co-ord position 
	@param y Y co-ord position
*/
void ERMCH1115_graphics::setCursor(int16_t x, int16_t y) {
	cursor_x = x;
	cursor_y = y;
}

/*! 
	@brief set the text size , starts at 1 
	@param s Size of text 1-X 
*/
void ERMCH1115_graphics::setTextSize(uint8_t s) {
	textsize = (s > 0) ? s : 1;
}

/*! 
	@brief set the text color  
	@param c Color fo text 
*/
void ERMCH1115_graphics::setTextColor(uint8_t c) {
	textcolor = textbgcolor = c;
}

/*! 
	@brief set the text color  
	@param c Color of text foreground
	@param b color of background of text 
*/
void ERMCH1115_graphics::setTextColor(uint8_t c, uint8_t b) {
	textcolor   = c;
	textbgcolor = b; 
}

/*!
	@brief turn on or off screen wrap of the text (fonts 1-6)
	@param w TRUE on
*/
void ERMCH1115_graphics::setTextWrap(boolean w) {
	wrap = w;
}

/*!
	@brief Gets rotation value 0-3
	@return value 0-3 for rotation 0-3 is mapped to  0 90 180 270 degrees
*/
uint8_t ERMCH1115_graphics::getRotation(void) const {
	return rotation;
}

/*!
	@brief Sets rotation value 0-3
	@param x value 0-3 for rotation 0-3 is mapped to  0 90 180 270 degrees
*/
void ERMCH1115_graphics::setRotation(uint8_t x) {
	rotation = (x & 3);
	switch(rotation) {
	 case 0:
	 case 2:
		_width  = WIDTH;
		_height = HEIGHT;
		break;
	 case 1:
	 case 3:
		_width  = HEIGHT;
		_height = WIDTH;
		break;
	}
}


/*!
	@brief Gets the width of the display (per current rotation)
	@return width member of display in pixels 
*/
int16_t ERMCH1115_graphics::width(void) const {
	return _width;
}
 
/*!
	@brief Gets the height of the display (per current rotation)
	@return height member of display in pixels 
*/
int16_t ERMCH1115_graphics::height(void) const {
	return _height;
}

/*!
	@brief sets the data addressing mode in drawBitmap function.
	@param  mode boolean mode  , true default
		-# True =  bitmap data vertically addressed 
		-# False = bitmap data horizontally addressed 
*/
void ERMCH1115_graphics::setDrawBitmapAddr(boolean mode) {
	drawBitmapAddr = mode;
}

/*!
	@brief   Set the current font type
	@param FontNumber 1-8 enum OLED_FONT_TYPE_e
	@note 1=default 2=thick 3=seven segment 4=wide 5=tiny 6=homespun 7=bignums 8=mednums
*/
void ERMCH1115_graphics::setFontNum(OLEDFontType_e  FontNumber) 
{
		_FontNumber = FontNumber;
		
	switch (_FontNumber) {
		case OLEDFontType_Default:  // Norm default 5 by 8
			_CurrentFontWidth = OLEDFontWidth_5;
			_CurrentFontoffset =  OLEDFontOffset_Extend;
			_CurrentFontheight = OLEDFontHeight_8;
		break; 
		case OLEDFontType_Thick: // Thick 7 by 8 (NO LOWERCASE LETTERS)
			_CurrentFontWidth = OLEDFontWidth_7;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
		break; 
		case OLEDFontType_SevenSeg:  // Seven segment 4 by 8
			_CurrentFontWidth = OLEDFontWidth_4;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
		break;
		case OLEDFontType_Wide : // Wide  8 by 8 (NO LOWERCASE LETTERS)
			_CurrentFontWidth = OLEDFontWidth_8;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
		break; 
		case OLEDFontType_Tiny:  // tiny 3 by 8
			_CurrentFontWidth = OLEDFontWidth_3;
			_CurrentFontoffset =  OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
		break;
		case OLEDFontType_Homespun: // homespun 7 by 8 
			_CurrentFontWidth = OLEDFontWidth_7;
			_CurrentFontoffset = OLEDFontOffset_Space;
			_CurrentFontheight = OLEDFontHeight_8;
		break;
		case OLEDFontType_Bignum : // big nums 16 by 32 (NUMBERS + : only)
			_CurrentFontWidth = OLEDFontWidth_16;
			_CurrentFontoffset = OLEDFontOffset_Number;
			_CurrentFontheight = OLEDFontHeight_32;
		break; 
		case OLEDFontType_Mednum: // med nums 16 by 16 (NUMBERS + : only)
			_CurrentFontWidth = OLEDFontWidth_16;
			_CurrentFontoffset =  OLEDFontOffset_Number;
			_CurrentFontheight = OLEDFontHeight_16;
		break;
		default: // if wrong font num passed in,  set to default
			_CurrentFontWidth = OLEDFontWidth_5;
			_CurrentFontoffset =  OLEDFontOffset_Extend;
			_CurrentFontheight = OLEDFontHeight_8;
			_FontNumber = OLEDFontType_Default;
		break;
	}
	
}

/*!
	@brief writes a char (c) on the OLED
	@param x X coordinate
	@param y Y coordinate
	@param c The ASCII character
	@param color 
	@param bg background color
	@note for font 7,8 only
*/
void ERMCH1115_graphics::drawCharNum(uint8_t x, uint8_t y, uint8_t c, uint8_t color , uint8_t bg) 
{
		if (_FontNumber < OLEDFontType_Bignum  ){return;}
		
		uint8_t i, j;
		uint8_t ctemp = 0, y0 = y; 

		for (i = 0; i < _CurrentFontheight*2; i++) {
			if (_FontNumber == OLEDFontType_Bignum){
				#ifdef CH1115_Font_Seven
					ctemp = pgm_read_byte(&pFontBigNumptr[c - _CurrentFontoffset][i]);
				#endif
			}else if(_FontNumber == OLEDFontType_Mednum) {
				#ifdef CH1115_Font_Eight
					ctemp = pgm_read_byte(&pFontMedNumptr[c - _CurrentFontoffset][i]);
				#endif
			}else 
			{
				c+=1; // get rid of unused variable compiler warning, in event the font undefined
				return;
			}
				for (j = 0; j < 8; j++) {
						if (ctemp & 0x80) {
								drawPixel(x, y, color);
						} else {
								drawPixel(x, y, bg);
						}
						ctemp <<= 1;
						y++;
						if ((y - y0) == _CurrentFontheight) {
								y = y0;
								x++;
								break;
						}
				}
		}
}

/*!
	@brief Writes text string (*ptext) on the OLED
	@param x X coordinate
	@param y Y coordinate
	@param pText pointer to string of ASCII character's
	@param color text color
	@param bg background color
	@note for font 7,8 only
*/
void ERMCH1115_graphics::drawTextNum(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg) 
{
		if (_FontNumber < OLEDFontType_Bignum){return;}
		while (*pText != '\0') 
		{
				if (x > (_width - _CurrentFontWidth )) 
				{
						x = 0;
						y += _CurrentFontheight ;
						if (y > (_height - _CurrentFontheight))  y = x = 0;
				}
				drawCharNum(x, y, *pText, color, bg);
				x += _CurrentFontWidth ;
				pText++;
		}
}

/*!
	@brief Writes text string on the OLED
	@param x X coordinate
	@param y Y coordinate
	@param pText pointer to string/array
	@param color text color
	@param bg background color
	@param size 1-x
	@note for font #1-6 only
*/
void ERMCH1115_graphics::drawText(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg, uint8_t size) {
     if (_FontNumber >= OLEDFontType_Bignum){return;}
    uint8_t cursor_x, cursor_y;
    cursor_x = x, cursor_y = y;
      while (*pText != '\0') 
      {
        if (wrap && ((cursor_x + size * _CurrentFontWidth) > _width)) 
        {
            cursor_x = 0;
            cursor_y = cursor_y + size * 7 + 3;
            if (cursor_y > _height) cursor_y = _height;
        }
        drawChar(cursor_x, cursor_y, *pText, color, bg, size);
        cursor_x = cursor_x + size * (_CurrentFontWidth + 1);
        if (cursor_x > _width) cursor_x = _width;
        pText++;
      }
}
