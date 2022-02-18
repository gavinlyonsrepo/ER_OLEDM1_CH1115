/*
* Project Name: ERMCH1115
* File: ERMCH1115.h
* Description: ER_OLEDM1 OLED driven by CH1115 controller source file
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
*/

#include "ER_OLEDM1_CH1115.h"

// Class Constructors // 4 off
// No buffer , Hardware + software SPI
// buffer, Hardware + software SPI 

#ifdef NO_BUFFER
// Hardware SPI
ERMCH1115  :: ERMCH1115(int8_t cd, int8_t rst, int8_t cs) 
{
  _OLED_CD = cd;
  _OLED_RST= rst;
  _OLED_CS = cs;
  _OLED_DIN = -1;   // -1 for din  specify using hardware SPI
  _OLED_SCLK = -1;    // -1 for  sclk specify using hardware SPI
}

// Software SPI
ERMCH1115  :: ERMCH1115(int8_t cd, int8_t rst, int8_t cs, int8_t sclk, int8_t din)
{
  _OLED_CD = cd;
  _OLED_RST= rst;
  _OLED_CS = cs;
  _OLED_DIN = din;  
  _OLED_SCLK = sclk;
}

#else

ERMCH1115  :: ERMCH1115(int8_t cd, int8_t rst, int8_t cs) :ERMCH1115_graphics(OLED_WIDTH, OLED_HEIGHT) 
{
  _OLED_CD = cd;
  _OLED_RST= rst;
  _OLED_CS = cs;
  _OLED_DIN = -1;   // -1 for din and sclk specify using hardware SPI
  _OLED_SCLK = -1;
}

// Software SPI
ERMCH1115  :: ERMCH1115(int8_t cd, int8_t rst, int8_t cs, int8_t sclk, int8_t din) :  ERMCH1115_graphics(OLED_WIDTH, OLED_HEIGHT) 
{
  _OLED_CD = cd;
  _OLED_RST= rst;
  _OLED_CS = cs;
  _OLED_DIN = din;  
  _OLED_SCLK = sclk;
}
#endif

// Desc: begin Method initialise OLED 
// Sets pinmodes and SPI setup
// Param1: OLEDcontrast default = 0x80 , range 0x00 to 0xFE
void ERMCH1115::OLEDbegin (uint8_t OLEDcontrast) 
{
  pinMode(_OLED_CD , OUTPUT);
  pinMode(_OLED_RST, OUTPUT);
  pinMode(_OLED_CS, OUTPUT);
  
  _OLEDcontrast  = OLEDcontrast ;
  
  if (isHardwareSPI()) 
  {
		SPI.begin();
  }else
  {
		pinMode(_OLED_DIN, OUTPUT);
		pinMode(_OLED_SCLK, OUTPUT);
  }
  
  OLEDinit();
}


// Desc: Called from OLEDbegin carries out Power on sequence and register init
// Can be used to reset OLED to default values.
void ERMCH1115::OLEDinit()
 {
	if (isHardwareSPI()) {SPI_TRANSACTION_START}
	ERMCH1115_CS_SetLow;
	
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
	ERMCH1115_CS_SetHigh;  
	if (isHardwareSPI()) {SPI_TRANSACTION_END}
	delay(ERMCH1115_INITDELAY);
}

// Desc: Sends a command to the display
// Param1: the command
// Param2: the values to change
void ERMCH1115::send_command (uint8_t command,uint8_t value) 
{
  ERMCH1115_CD_SetLow; 
  send_data(command | value);
  ERMCH1115_CD_SetHigh;
}

// Desc: Resets OLED in a four wire setup called at start 
void ERMCH1115::OLEDReset () 
{
	ERMCH1115_RST_SetHigh; 
	delay(ERMCH1115_RST_DELAY1);
	ERMCH1115_RST_SetLow;
	delay(ERMCH1115_RST_DELAY1);
	ERMCH1115_RST_SetHigh ;
	delay(ERMCH1115_RST_DELAY2);
}

// Desc: Turns On Display
// Param1: bits,  1  on , 0 off
void ERMCH1115::OLEDEnable (uint8_t bits) 
{
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;
 if (bits)
 {
	  _sleep= false;
	  send_command(ERMCH1115_DISPLAY_ON, 0);
 }else
 {
	 _sleep= true;
	 send_command(ERMCH1115_DISPLAY_OFF, 0);
 }
 ERMCH1115_CS_SetHigh;
 if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: OLEDIsOff
// Returns: bool  value of _sleep if true OLED is off and in sleep mode, 500uA.
bool ERMCH1115::OLEDIssleeping() { return  _sleep ;}

// Desc: Sets up Horionztal Scroll
// Param1: TimeInterval 0x00 -> 0x07 , 0x00 = 6 frames
// Param2: Direction 0x26 right 0x27 left (A2 – A0)
// Param3: Mode. Set Scroll Mode: (28H – 2BH)  0x28 = continuous
void ERMCH1115::OLEDscrollSetup(uint8_t Timeinterval, uint8_t Direction, uint8_t mode) 
{
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;

 send_command(ERMCH1115_HORIZONTAL_A_SCROLL_SETUP, 0);
 send_command(ERMCH1115_HORIZONTAL_A_SCROLL_SET_SCOL, 0);
 send_command(ERMCH1115_HORIZONTAL_A_SCROLL_SET_ECOL, 0);

 send_command(Direction , 0);
 send_command(ERMCH1115_SPAGE_ADR_SET , 0);
 send_command(Timeinterval , 0);
 send_command(ERMCH1115_EPAGE_ADR_SET , 0);

 send_command(mode, 0);
  
 ERMCH1115_CS_SetHigh;
 if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: Turns on Horizontal scroll 
// Param1: bits 1  on , 0 off
// Note OLEDscrollSetup must be called before it 
void ERMCH1115::OLEDscroll(uint8_t bits) 
{
	if (isHardwareSPI()) {SPI_TRANSACTION_START}
	ERMCH1115_CS_SetLow;
	bits ? send_command(ERMCH1115_ACTIVATE_SCROLL , 0) :   send_command(ERMCH1115_DEACTIVATE_SCROLL, 0);
	ERMCH1115_CS_SetHigh;
	if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: Adjusts contrast 
// Param1: Contrast 0x00 to 0xFF , default 0x80
// Note: Setup during init. 
void ERMCH1115::OLEDContrast(uint8_t contrast)
{
	if (isHardwareSPI()) {SPI_TRANSACTION_START}
	ERMCH1115_CS_SetLow;
	send_command(ERMCH115_CONTRAST_CONTROL  ,0); 
	send_command(contrast, 0);  
	ERMCH1115_CS_SetHigh;
	if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: Rotates the display vertically 
// Param1: bits 1  on , 0 off
void ERMCH1115::OLEDFlip(uint8_t  bits) 
{
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;
  
  bits ? send_command(ERMCH1115_COMMON_SCAN_DIR, 0x08):send_command(ERMCH1115_COMMON_SCAN_DIR, 0x00)  ; // C0H - C8H 
  bits ? send_command(ERMCH1115_SEG_SET_REMAP, 0x01):   send_command(ERMCH1115_SEG_SET_REMAP, 0x00); //(A0H - A1H)
 
  ERMCH1115_CS_SetHigh;
  if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: Turns on fade effect 
// Param1: bits  
// bits = 0x00 to stop  
// bits values: (see datasheet breatheffect P25 for more details)
// 		ON/OFF * * A4 A3 A2 A1 A0
//      When ON/OFF =”H”, Breathing Light ON.
//	 	Breathing Display Effect Maximum Brightness Adjust Set: (A4 – A3)
//		Breathing Display Effect Time Interval Set: (A2 – A0)
// 		Default on is 0x81
void ERMCH1115::OLEDfadeEffect(uint8_t bits) 
{
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;
 send_command(ERMCCH1115_BREATHEFFECT_SET,0);
 send_command(bits,0);
 ERMCH1115_CS_SetHigh;
 if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Call when powering down
void ERMCH1115::OLEDPowerDown(void)
{
	OLEDEnable(0);
	ERMCH1115_CD_SetLow ;
	ERMCH1115_RST_SetLow ;
	ERMCH1115_CS_SetLow;
	if(isHardwareSPI() == false)
	{
		ERMCH1115_SCLK_SetLow;
		ERMCH1115_SDA_SetLow ;
	}
	_sleep= true;
}

// Desc: invert the display
// Param1: bits, 1 invert , 0 normal
void ERMCH1115::OLEDInvert(uint8_t bits) 
{
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;
  bits ? send_command(ERMCH1115_DISPLAY_INVERT, 0) :   send_command(ERMCH1115_DISPLAY_NORMAL, 0);
 ERMCH1115_CS_SetHigh;
 if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: Fill the screen NOT the buffer with a datapattern 
// Param1: datapattern can be set to zero to clear screen (not buffer) range 0x00 to 0ff
// Param2: optional delay in milliseconds can be set to zero normally.
void ERMCH1115::OLEDFillScreen(uint8_t dataPattern, uint8_t delay) 
{
	for (uint8_t row = 0; row < OLED_PAGE_NUM; row++) 
	{
		OLEDFillPage(row,dataPattern,delay);
	}
}

// Desc: Fill the chosen page(1-8)  with a datapattern 
// Param1: datapattern can be set to 0 to FF (not buffer)
// Param2: optional delay in milliseconds can be set to zero normally.
void ERMCH1115::OLEDFillPage(uint8_t page_num, uint8_t dataPattern,uint8_t mydelay) 
{
	if (isHardwareSPI()) {SPI_TRANSACTION_START}
	ERMCH1115_CS_SetLow;
	send_command(ERMCH1115_SET_COLADD_LSB, 0); 
	send_command(ERMCH1115_SET_COLADD_MSB, 0);
	send_command(ERMCH1115_SET_PAGEADD, page_num); 
	ERMCH1115_CS_SetHigh;
	delayMicroseconds(2);
	ERMCH1115_CS_SetLow;
	uint8_t numofbytes = OLED_WIDTH; // 128 bytes
	for (uint8_t i = 0; i < numofbytes; i++) 
	{
	  send_data(dataPattern);
	  delay(mydelay);
	}
	ERMCH1115_CS_SetHigh;
	if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

//Desc: Draw a bitmap in PROGMEM to the screen
//Param1: x offset 0-128
//Param2: y offset 0-64
//Param3: width 0-128
//Param4 height 0-64
//Param5 the bitmap must be in PROGMEM
void ERMCH1115::OLEDBitmap(int16_t x, int16_t y, uint8_t w, uint8_t h, const uint8_t* data) 
{
 #if defined(ESP8266)
  // ESP8266 needs a periodic yield() call to avoid watchdog reset.
  yield();
#endif
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;

  uint8_t tx, ty; 
  uint16_t offset = 0; 
  uint8_t column = (x < 0) ? 0 : x;
  uint8_t page = (y < 0) ? 0 : y >>3;

  for (ty = 0; ty < h; ty = ty + 8) 
  {
		if (y + ty < 0 || y + ty >= OLED_HEIGHT) {continue;}
		send_command(ERMCH1115_SET_COLADD_LSB, (column & 0x0F)); 
		send_command(ERMCH1115_SET_COLADD_MSB, (column & 0xF0) >> 4);
		send_command(ERMCH1115_SET_PAGEADD, page++); 

		for (tx = 0; tx < w; tx++) 
		{
			  if (x + tx < 0 || x + tx >= OLED_WIDTH) {continue;}
			  offset = (w * (ty >> 3)) + tx; 
			  send_data(pgm_read_byte(&data[offset]));
		}
  }
ERMCH1115_CS_SetHigh;
if (isHardwareSPI()) {SPI_TRANSACTION_END}
#if defined(ESP8266)
  yield();
#endif
}

// Desc: Checks if software SPI is on
// Returns: true 1 if hardware SPi on , false 0 for software spi
bool ERMCH1115::isHardwareSPI() 
{
  return (_OLED_DIN == -1 && _OLED_SCLK == -1);
}

// Desc: used in software SPI mode to shift out data
// Param1: bit order LSB or MSB set to MSBFIRST for ERMCH1115
// Param2: the byte to go
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
		delayMicroseconds(ERMCH1115_HIGHFREQ_DELAY); // optional, for high freq MCU 
		ERMCH1115_SCLK_SetLow;  
		delayMicroseconds(ERMCH1115_HIGHFREQ_DELAY);
	}
}

//Desc: Send data byte with SPI to ERMCH1115
//Param1: the data byte
void ERMCH1115::send_data(uint8_t byte)
{
  if (isHardwareSPI()) 
  {
	(void)SPI.transfer(byte); 
  }else
  {
	CustomshiftOut(MSBFIRST, byte); // README note 21
  }
} 

// ******************************************************
// Functions below not needed for no_buffer mode 
// *******************************************************
#ifndef NO_BUFFER

// Desc init the Multibuffer struct
// Param 1 Pointer to a struct
// Param 2 Pointer to buffer array data(arrays decay to  pointers)
// Param 3. width of buffer
// Param 4. height of buffer
// Param 5. x offset of buffer
// Param 6. y offset of buffer
#ifdef MULTI_BUFFER
void ERMCH1115::OLEDinitBufferStruct(MultiBuffer* mystruct, uint8_t* mybuffer, uint8_t w,  uint8_t h, int16_t  x, int16_t y)
{
   mystruct->screenbitmap = mybuffer; // point it to the buffer
   mystruct->width = w ;
   mystruct->height = h;
   mystruct->xoffset = x;
   mystruct->yoffset = y; 
}
#endif


//Desc: updates the buffer i.e. writes it to the screen
void ERMCH1115::OLEDupdate() 
{

#ifdef MULTI_BUFFER
	  OLEDBuffer( this->ActiveBuffer->xoffset, this->ActiveBuffer->yoffset, this->ActiveBuffer->width, this->ActiveBuffer->height, (uint8_t*) this->ActiveBuffer->screenbitmap); 
	  return;
#endif

#ifdef SINGLE_BUFFER
  uint8_t x = 0; uint8_t y = 0; uint8_t w = this->bufferWidth; uint8_t h = this->bufferHeight;
  OLEDBuffer( x,  y,  w,  h, (uint8_t*) this->buffer);
#endif
}

//Desc: clears the buffer i.e. does NOT write to the screen
void ERMCH1115::OLEDclearBuffer()
{
#ifdef MULTI_BUFFER
   memset( this->ActiveBuffer->screenbitmap, 0x00, (this->ActiveBuffer->width * (this->ActiveBuffer->height/ 8))  ); 
   return;
#endif

#ifdef SINGLE_BUFFER
  memset( this->buffer, 0x00, (this->bufferWidth * (this->bufferHeight /8))  ); 
#endif
}

//Desc: Draw a bitmap to the screen
//Param1: x offset 0-128
//Param2: y offset 0-64
//Param3: width 0-128
//Param4 height 0-64
//Param5 the bitmap
//Note: Called by OLEDupdate
void ERMCH1115::OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data) 
{
 #if defined(ESP8266)
  yield();
#endif
 if (isHardwareSPI()) {SPI_TRANSACTION_START}
 ERMCH1115_CS_SetLow;

  uint8_t tx, ty; 
  uint16_t offset = 0; 
  uint8_t column = (x < 0) ? 0 : x;
  uint8_t page = (y < 0) ? 0 : y/8;

  for (ty = 0; ty < h; ty = ty + 8) 
  {
	if (y + ty < 0 || y + ty >= OLED_HEIGHT) {continue;}
	
	send_command(ERMCH1115_SET_COLADD_LSB, (column & 0x0F)); 
	send_command(ERMCH1115_SET_COLADD_MSB, (column & 0XF0) >> 4); 
	send_command(ERMCH1115_SET_PAGEADD, page++); 
 
	for (tx = 0; tx < w; tx++) 
	{
		  if (x + tx < 0 || x + tx >= OLED_WIDTH) {continue;}
		  offset = (w * (ty /8)) + tx; 
		  send_data(data[offset++]);
	}
  }
  
  
ERMCH1115_CS_SetHigh;
if (isHardwareSPI()) {SPI_TRANSACTION_END}
#if defined(ESP8266)
  yield();
#endif
}

// Desc: Draws a Pixel to the screen overides the  graphics library
// Passed x and y co-ords and colour of pixel.
void ERMCH1115::drawPixel(int16_t x, int16_t y, uint8_t colour) 
{
	
#ifdef MULTI_BUFFER
  if ((x < 0) || (x >= this->ActiveBuffer->width) || (y < 0) || (y >= this->ActiveBuffer->height)) {
	return;
  }
	  uint16_t offset = (this->ActiveBuffer->width * (y/8)) + x; 
	  switch (colour)
	  {
		case FOREGROUND: this->ActiveBuffer->screenbitmap[offset] |= (1 << (y & 7)); break;
		case BACKGROUND: this->ActiveBuffer->screenbitmap[offset] &= ~(1 << (y & 7)); break;
		case INVERSE: this->ActiveBuffer->screenbitmap[offset] ^= (1 << (y & 7)); break;
	  }
	return;
#endif
	
#ifdef SINGLE_BUFFER
  if ((x < 0) || (x >= this->bufferWidth) || (y < 0) || (y >= this->bufferHeight)) {
	return;
  }
	  uint16_t tc = (bufferWidth * (y /8)) + x; 
	  switch (colour)
	  {
		case FOREGROUND:  this->buffer[tc] |= (1 << (y & 7)); break;
		case BACKGROUND:  this->buffer[tc] &= ~(1 << (y & 7)); break;
		case INVERSE: this->buffer[tc] ^= (1 << (y & 7)); break;
	  }
#endif
}


#else // NO BUFFER functions
// ***************************************************
//  these functions below are not needed by buffers modes
// and only used in "no buffer" mode. 
// ***********************************************

// Desc: goes to XY position
// Param1 : column 0-128
// Param2  : page 0-7
void ERMCH1115::OLEDNoBufferGotoXY(uint8_t column , uint8_t page)
{
		if (isHardwareSPI()) {SPI_TRANSACTION_START}
		ERMCH1115_CS_SetLow;
		send_command(ERMCH1115_SET_COLADD_LSB, (column & 0x0F)); 
		send_command(ERMCH1115_SET_COLADD_MSB, (column & 0xF0) >> 4);
		send_command(ERMCH1115_SET_PAGEADD, page++); 
		ERMCH1115_CS_SetHigh;
		if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: draws passed character.
// Param1: character 'A' or number in  the ASCII table 1-127(default)
void ERMCH1115::OLEDNoBufferChar(unsigned char character)
{
	if (isHardwareSPI()) {SPI_TRANSACTION_START}
	ERMCH1115_CS_SetLow;
	NO_BUFFER_FONTPADDING;
	for (uint8_t column = 0 ; column <  NO_BUFFER_FONTWIDTH ; column++)
	{
	send_data(pgm_read_byte(CH_Font_One + (((character-NO_BUFFER_ASCII_OFFSET)*NO_BUFFER_FONTWIDTH)) + column));
	}
	NO_BUFFER_FONTPADDING;
	ERMCH1115_CS_SetHigh;
	if (isHardwareSPI()) {SPI_TRANSACTION_END}
}

// Desc: draws passed  character array
// Param1: pointer to start of character array
void ERMCH1115::OLEDNoBufferString(const  unsigned char *characters)
{
	if (isHardwareSPI()) {SPI_TRANSACTION_START}
	ERMCH1115_CS_SetLow;
	char index;
	while (*characters)
	{
	index = *characters++;
	NO_BUFFER_FONTPADDING;
	for (uint8_t column = 0 ; column <  NO_BUFFER_FONTWIDTH ; column++)
	{
		send_data(pgm_read_byte(CH_Font_One + (((index-NO_BUFFER_ASCII_OFFSET)*NO_BUFFER_FONTWIDTH)) + column));
	}
	NO_BUFFER_FONTPADDING;
	
	};
	ERMCH1115_CS_SetHigh;
	if (isHardwareSPI()) {SPI_TRANSACTION_END}
}
#endif
//***********************************************
