 /*!
	@file ER_OLEDM1_CH1115.cpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller Source file
	Project Name: ER_OLEDM1_CH1115 , URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@author  Gavin Lyons
*/

#include "ER_OLEDM1_CH1115.hpp"

// == Class Constructors  ==

/*!
	@brief init the screen/sharedBuffer object
	@param mybuffer Pointer to buffer array data(arrays decay to  pointers)
	@param w width of buffer
	@param h height of buffer
	@param x offset of buffer
	@param y offset of buffer
 */
ERMCH1115_SharedBuffer::ERMCH1115_SharedBuffer(uint8_t* mybuffer, uint8_t w,  uint8_t h, int16_t  x, int16_t y)
{
	screenBuffer = mybuffer; // pointer to buffer
	width = w;   // bitmap x size
	height = h; // bitmap y size
	xoffset = x; // x offset
	yoffset = y; // y offset
}

/*!
	@brief init the OLED class object
	@param oledwidth
	@param oledheight
	@param cd GPIO data or command
	@param rst GPIO reset
	@param cs GPIO Chip select
	@note Hardware SPI version
 */
ERMCH1115  :: ERMCH1115(int16_t oledwidth , int16_t oledheight, int8_t cd, int8_t rst, int8_t cs) :ERMCH1115_graphics(oledwidth , oledheight)
{
	_OLED_CD = cd;
	_OLED_RST= rst;
	_OLED_CS = cs;
	_WidthScreen = oledwidth ; 
	_HeightScreen = oledheight ;
	_isHardwareSPI = 2; // HW SPI mode = 2
}

/*!
	@brief init the OLED class object
	@param oledwidth
	@param oledheight
	@param cd GPIO data or command
	@param rst GPIO reset
	@param cs GPIO Chip select
	@param sclk GPIO SPI Clock
	@param din GPIO MOSI
	@note software SPI version
 */
ERMCH1115  :: ERMCH1115(int16_t oledwidth , int16_t oledheight, int8_t cd, int8_t rst, int8_t cs, int8_t sclk, int8_t din) :  ERMCH1115_graphics(oledwidth ,  oledheight)
{
	_OLED_CD = cd;
	_OLED_RST= rst;
	_OLED_CS = cs;
	_OLED_DIN = din;
	_OLED_SCLK = sclk;
	_WidthScreen = oledwidth ; 
	_HeightScreen = oledheight ;
	_isHardwareSPI = 3; // SW SPI mode = 3
}

// == Methods ==

/*!
	@brief begin Method initialise OLED Sets pinmodes and SPI setup
	@param OLEDcontrast Contrast of the OLED display default = 0x80 , range 0x00 to 0xFE
 */
void ERMCH1115::OLEDbegin (uint8_t OLEDcontrast)
{
	_OLEDcontrast  = OLEDcontrast ;
	switch (_isHardwareSPI)
	{
		case 2:
			pinMode(_OLED_CD , OUTPUT);
			pinMode(_OLED_RST, OUTPUT);
			pinMode(_OLED_CS, OUTPUT);
			SPI.begin();
		break;
		case 3:
			pinMode(_OLED_CD , OUTPUT);
			pinMode(_OLED_RST, OUTPUT);
			pinMode(_OLED_CS, OUTPUT);
			pinMode(_OLED_DIN, OUTPUT);
			pinMode(_OLED_SCLK, OUTPUT);
		break;
	}
	OLEDinit();
}

/*!
	@brief Called from OLEDbegin carries out Power on sequence and register init
	@note Can be used to reset OLED to default values.
*/
void ERMCH1115::OLEDinit()
 {
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: 
			ERMCH1115_CS_SetLow; 
		break;
	}

	OLEDReset();

	send_command(ERMCH1115_DISPLAY_OFF, 0);

	send_command(ERMCH1115_SET_COLADD_LSB, 0);
	send_command(ERMCH1115_SET_COLADD_MSB, 0);
	send_command(ERMCH1115_SET_PAGEADD, 0);
	send_command(ERMCH115_SET_DISPLAY_START_LINE, 0);

	send_command(ERMCH115_CONTRAST_CONTROL  ,0);
	send_command(_OLEDcontrast, 0);

	send_command(ERMCH1115_IREF_REG, 0);
	send_command(ERMCH1115_IREF_SET, 0);

	send_command(ERMCH1115_SEG_SET_REMAP, 0);
	send_command(ERMCH1115_SEG_SET_PADS, 0);
	send_command(ERMCH1115_ENTIRE_DISPLAY_ON, 0);
	send_command(ERMCH1115_DISPLAY_NORMAL, 0);

	send_command(ERMCH1115_MULTIPLEX_MODE_SET, 0);
	send_command(ERMCH1115_MULTIPLEX_DATA_SET , 0);

	send_command(ERMCH1115_COMMON_SCAN_DIR, 0);

	send_command(ERMCH1115_OFFSET_MODE_SET, 0);
	send_command(ERMCH1115_OFFSET_DATA_SET, 0);

	send_command(ERMCH1115_OSC_FREQ_MODE_SET, 0);
	send_command(ERMCH1115_OSC_FREQ_DATA_SET, 0);

	send_command(ERMCH1115_PRECHARGE_MODE_SET, 0);
	send_command(ERMCH1115_PRECHARGE_DATA_SET, 0);

	send_command(ERMCH1115_COM_LEVEL_MODE_SET, 0);
	send_command(ERMCH1115_COM_LEVEL_DATA_SET, 0);

	send_command(ERMCH1115_SET_PUMP_REG, ERMCH115_SET_PUMP_SET);

	send_command(ERMCH1115_DC_MODE_SET, 0);
	send_command(ERMCH1115_DC_ONOFF_SET, 0);

	send_command(ERMCH1115_DISPLAY_ON, 0);
	_sleep= false;
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
	delay(ERMCH1115_INITDELAY);
}

/*!
	 @brief Sends a command to the display
	 @param command Command to send
	 @param value the values to change
	 @note command and value  will be combined with OR
*/
void ERMCH1115::send_command (uint8_t command,uint8_t value)
{
	ERMCH1115_CD_SetLow;
	send_data(command | value);
	ERMCH1115_CD_SetHigh;
}

/*!
	 @brief Resets OLED in a four wire setup called at start
*/
void ERMCH1115::OLEDReset ()
{
	ERMCH1115_RST_SetHigh;
	delay(ERMCH1115_RST_DELAY1);
	ERMCH1115_RST_SetLow;
	delay(ERMCH1115_RST_DELAY1);
	ERMCH1115_RST_SetHigh ;
	delay(ERMCH1115_RST_DELAY2);
}

/*!
	 @brief Turns On Display
	 @param bits  1  display on , 0 display off
*/
void ERMCH1115::OLEDEnable (uint8_t bits)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}
	if (bits)
	{
		_sleep= false;
		send_command(ERMCH1115_DISPLAY_ON, 0);
	}else
	{
	 _sleep= true;
	 send_command(ERMCH1115_DISPLAY_OFF, 0);
	}
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	@brief getting for _sleep memebr . is OLED in sleep mode
	@returns value of _sleep if true OLED is off and in sleep mode, 500uA.
*/
bool ERMCH1115::OLEDIssleeping() { return  _sleep ;}

/*!
	@brief Sets up Horizontal Scroll
	@param TimeInterval 0x00 -> 0x07 , 0x00 = 6 frames
	@param Direction 0x26 right 0x27 left (A2 – A0)
	@param mode Set Scroll Mode: (28H – 2BH)  0x28 = continuous
*/
void ERMCH1115::OLEDscrollSetup(uint8_t TimeInterval, uint8_t Direction, uint8_t mode)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}

	send_command(ERMCH1115_HORIZONTAL_A_SCROLL_SETUP, 0);
	send_command(ERMCH1115_HORIZONTAL_A_SCROLL_SET_SCOL, 0);
	send_command(ERMCH1115_HORIZONTAL_A_SCROLL_SET_ECOL, 0);

	send_command(Direction , 0);
	send_command(ERMCH1115_SPAGE_ADR_SET , 0);
	send_command(TimeInterval , 0);
	send_command(ERMCH1115_EPAGE_ADR_SET , 0);

	send_command(mode, 0);

	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	@brief Turns on Horizontal scroll
	@param bits 1  Horizontal scroll on , 0 Horizontal scroll off
	@note OLEDscrollSetup must be called before it
*/
void ERMCH1115::OLEDscroll(uint8_t bits)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}
	bits ? send_command(ERMCH1115_ACTIVATE_SCROLL , 0) :   send_command(ERMCH1115_DEACTIVATE_SCROLL, 0);
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	@brief Adjusts contrast
	@param contrast 0x00 to 0xFF , default 0x80
	@note Setup during init.
*/
void ERMCH1115::OLEDContrast(uint8_t contrast)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}
	send_command(ERMCH115_CONTRAST_CONTROL  ,0);
	send_command(contrast, 0);
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	@brief Rotates the display vertically
	@param bits 1  on , 0 off
*/
void ERMCH1115::OLEDFlip(uint8_t  bits)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}

	bits ? send_command(ERMCH1115_COMMON_SCAN_DIR, 0x08):send_command(ERMCH1115_COMMON_SCAN_DIR, 0x00)  ; // C0H - C8H
	bits ? send_command(ERMCH1115_SEG_SET_REMAP, 0x01):   send_command(ERMCH1115_SEG_SET_REMAP, 0x00); //(A0H - A1H)

	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	@brief Turns on fade effect
	@param bits 0x00 to stop
	@note bits values: (see datasheet breatheffect P25 for more details)
		-# ON/OFF * * A4 A3 A2 A1 A0
		-# When ON/OFF =”H”, Breathing Light ON.
		-# Breathing Display Effect Maximum Brightness Adjust Set: (A4 – A3)
		-# Breathing Display Effect Time Interval Set: (A2 – A0)
		-# Default on is 0x81
*/
void ERMCH1115::OLEDfadeEffect(uint8_t bits)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}
	send_command(ERMCCH1115_BREATHEFFECT_SET,0);
	send_command(bits,0);
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
 @brief  Call when powering down OLED , disables OLED/SPI and sets all GPIO low.
*/
void ERMCH1115::OLEDPowerDown(void)
{
	OLEDEnable(0);
	
	switch (_isHardwareSPI)
	{
		case 2:
			SPI.end();
			ERMCH1115_CD_SetLow ;
			ERMCH1115_RST_SetLow ;
			ERMCH1115_CS_SetLow;
		break;
		case 3:
			ERMCH1115_CD_SetLow ;
			ERMCH1115_RST_SetLow ;
			ERMCH1115_CS_SetLow;
			ERMCH1115_SCLK_SetLow;
			ERMCH1115_SDA_SetLow ;
		break;
	}
	_sleep= true;
}

/*!
	 @brief invert the display
	 @param bits 1 invert , 0 normal
*/
void ERMCH1115::OLEDInvert(uint8_t bits)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}
	bits ? send_command(ERMCH1115_DISPLAY_INVERT, 0) :   send_command(ERMCH1115_DISPLAY_NORMAL, 0);
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	 @brief Fill the screen NOT the buffer with a datapattern
	 @param dataPattern can be set to zero to clear screen (not buffer) range 0x00 to 0ff
	 @param delay optional delay in milliseconds can be set to zero normally.
*/
void ERMCH1115::OLEDFillScreen(uint8_t dataPattern, uint8_t delay)
{
	for (uint8_t row = 0; row < (_HeightScreen/8); row++)
	{
		OLEDFillPage(row,dataPattern,delay);
	}
}

/*!
	 @brief Fill the chosen page(1-8)  with a datapattern
	 @param pageNum  page 1-8 divides 64 pixel screen into 8 pages or blocks  64/8  
	 @param dataPattern can be set to 0 to FF (not buffer)
	 @param mydelay optional delay in milliseconds can be set to zero normally.
*/
void ERMCH1115::OLEDFillPage(uint8_t pageNum, uint8_t dataPattern,uint8_t mydelay)
{
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}
	send_command(ERMCH1115_SET_COLADD_LSB, 0);
	send_command(ERMCH1115_SET_COLADD_MSB, 0);
	send_command(ERMCH1115_SET_PAGEADD, pageNum);
	ERMCH1115_CS_SetHigh;
	delayMicroseconds(2);
	ERMCH1115_CS_SetLow;
	uint8_t numofbytes = _WidthScreen; // 128 bytes
	for (uint8_t i = 0; i < numofbytes; i++)
	{
		send_data(dataPattern);
		delay(mydelay);
	}
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
}

/*!
	 @brief Draw a bitmap in PROGMEM to the screen
	 @param x offset 0-128
	 @param y offset 0-64
	 @param w width 0-128
	 @param h height 0-64
	 @param data  pointer to the bitmap must be in PROGMEM
	 @return CH1115_Return_Codes_e enum
*/
CH1115_Return_Codes_e ERMCH1115::OLEDBitmap(int16_t x, int16_t y, uint8_t w, uint8_t h, const uint8_t* data)
{
// User error checks
// 1. bitmap is null
if (data == nullptr){return CH1115_BitmapNullptr ;}
// 2. Start point Completely out of bounds
if (x > _width || y > _height){return CH1115_BitmapScreenBounds;}
// 3. bitmap weight and height
if (w > _width || h > _height){return CH1115_BitmapLargerThanScreen ;}
// 4A.check vertical bitmap h must be divisible
if((h % 8 != 0)){return CH1115_BitmapVerticalSize;}

 #if defined(ESP8266)
	// ESP8266 needs a periodic yield() call to avoid watchdog reset.
	yield();
#endif
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}

	uint8_t tx, ty;
	uint16_t offset = 0;
	uint8_t column = (x < 0) ? 0 : x;
	uint8_t page = (y < 0) ? 0 : y >>3;

	for (ty = 0; ty < h; ty = ty + 8)
	{
		if (y + ty < 0 || y + ty >= _HeightScreen) {continue;}
		send_command(ERMCH1115_SET_COLADD_LSB, (column & 0x0F));
		send_command(ERMCH1115_SET_COLADD_MSB, (column & 0xF0) >> 4);
		send_command(ERMCH1115_SET_PAGEADD, page++);

		for (tx = 0; tx < w; tx++)
		{
				if (x + tx < 0 || x + tx >= _WidthScreen) {continue;}
				offset = (w * (ty >> 3)) + tx;
				send_data(pgm_read_byte(&data[offset]));
		}
	}
	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
#if defined(ESP8266)
	yield();
#endif
return CH1115_Success;
}


/*!
	 @brief used in software SPI mode to shift out data
	 @param bitOrder LSB or MSB set to MSBFIRST for ERMCH1115
	 @param value the byte to go out 
*/
void ERMCH1115::CustomshiftOut(uint8_t bitOrder, uint8_t value)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		if (bitOrder == LSBFIRST)
			!!(value & (1 << i)) ? ERMCH1115_SDA_SetHigh : ERMCH1115_SDA_SetLow ;
		else
			!!(value & (1 << (7 - i))) ? ERMCH1115_SDA_SetHigh : ERMCH1115_SDA_SetLow ;

		ERMCH1115_SCLK_SetHigh;
		delayMicroseconds(_HighFreqDelay); // optional, for high freq MCU
		ERMCH1115_SCLK_SetLow;
		delayMicroseconds(_HighFreqDelay);
	}
}

/*!
	 @brief Send data byte with SPI to ERMCH1115
	 @param byte the data byte to send 
*/
void ERMCH1115::send_data(uint8_t byte)
{
	switch (_isHardwareSPI)
	{
		case 2 :   (void)SPI.transfer(byte); break; 
		case 3 :  CustomshiftOut(MSBFIRST, byte); break; 
	}
}

/*!
	 @brief updates the OLED i.e. writes the active shared buffer to the screen
*/
void ERMCH1115::OLEDupdate()
{
	 OLEDBuffer( this->ActiveBufferPtr->xoffset, this->ActiveBufferPtr->yoffset, this->ActiveBufferPtr->width, this->ActiveBufferPtr->height, (uint8_t*) this->ActiveBufferPtr->screenBuffer);
}

/*!
	 @brief clears the active shared buffer i.e. does NOT write to the screen
*/
void ERMCH1115::OLEDclearBuffer()
{
	memset(this->ActiveBufferPtr->screenBuffer, 0x00, (this->ActiveBufferPtr->width * (this->ActiveBufferPtr->height/ 8))  );
}

/*!
	 @brief Draw a bitmap to the screen
	 @param x offset 0-128
	 @param y offset 0-64
	 @param w width 0-128
	 @param h height 0-64
	 @param data pointer to the bitmap data array
	 @note Called by OLEDupdate
*/
void ERMCH1115::OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data)
{
 #if defined(ESP8266)
	yield();
#endif
	switch (_isHardwareSPI)
	{
		case 2: 
			SPI_TRANSACTION_START;
			ERMCH1115_CS_SetLow; 
		break;
		case 3: ERMCH1115_CS_SetLow; break;
	}

	uint8_t tx, ty;
	uint16_t offset = 0;
	uint8_t column = (x < 0) ? 0 : x;
	uint8_t page = (y < 0) ? 0 : y/8;

	for (ty = 0; ty < h; ty = ty + 8)
	{
	if (y + ty < 0 || y + ty >= _HeightScreen) {continue;}

	send_command(ERMCH1115_SET_COLADD_LSB, (column & 0x0F));
	send_command(ERMCH1115_SET_COLADD_MSB, (column & 0XF0) >> 4);
	send_command(ERMCH1115_SET_PAGEADD, page++);

	for (tx = 0; tx < w; tx++)
	{
			if (x + tx < 0 || x + tx >= _WidthScreen) {continue;}
			offset = (w * (ty /8)) + tx;
			send_data(data[offset++]);
	}
	}


	switch (_isHardwareSPI)
	{
		case 2: 
			ERMCH1115_CS_SetHigh;
			SPI_TRANSACTION_END;
		break;
		case 3: ERMCH1115_CS_SetHigh; break;
	}
#if defined(ESP8266)
	yield();
#endif
}

/*!
	@brief Draws a Pixel to the screen overides the  graphics library 
	@param x x co-ord of pixel
	@param y y co-ord of pixel
	@param colour colour of  pixel
*/
void ERMCH1115::drawPixel(int16_t x, int16_t y, uint8_t colour)
{

	if ((x < 0) || (x >= this->ActiveBufferPtr->width) || (y < 0) || (y >= this->ActiveBufferPtr->height)) {
	return;
	}
	// Check rotation 
	int16_t temp;
	uint8_t RotateMode = getRotation();
	switch (RotateMode) {
	case 1:
		temp = x;
		x = WIDTH - 1 - y;
		y = temp;
	break;
	case 2:
		x = WIDTH - 1 - x;
		y = HEIGHT - 1 - y;
	break;
	case 3:
		temp = x;
		x = y;
		y = HEIGHT - 1 - temp;
	break;
	}
	uint16_t offset = (this->ActiveBufferPtr->width * (y/8)) + x;
	switch (colour)
	{
		case OLED_WHITE: this->ActiveBufferPtr->screenBuffer[offset] |= (1 << (y & 7)); break;
		case OLED_BLACK: this->ActiveBufferPtr->screenBuffer[offset] &= ~(1 << (y & 7)); break;
		case OLED_INVERSE : this->ActiveBufferPtr->screenBuffer[offset] ^= (1 << (y & 7)); break;
	}

}

/*!
	@brief Library version number getter
	@return The lib version number eg 180 = 1.8.0
*/
uint16_t ERMCH1115::OLEDLibVerNumGet(void) {return _LibVersionNum;}

/*!
	@brief Freq delay used in SW SPI getter, uS delay used in SW SPI method
	@return The  GPIO communications delay in uS
*/
uint16_t ERMCH1115::OLEDHighFreqDelayGet(void){return _HighFreqDelay;}

/*!
	@brief Freq delay used in SW SPI setter, uS delay used in SW SPI method
	@param CommDelay The GPIO communications delay in uS
*/
void  ERMCH1115::OLEDHighFreqDelaySet(uint16_t CommDelay){_HighFreqDelay = CommDelay;}
//  == EOF ==
