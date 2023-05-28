 /*!
	@file ER_OLEDM1_CH1115.hpp
	@brief ER_OLEDM1 OLED driven by CH1115 controller header file
	Project Name: ER_OLEDM1_CH1115 , URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115
	@author  Gavin Lyons
*/

#ifndef  _ER_OLEDM1_CH1115_H_
#define _ER_OLEDM1_CH1115_H_

// ** INCLUDES **
#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <SPI.h>
#include "ER_OLEDM1_CH1115_graphics.hpp"

// ** DEFINES **

// Display Pixel colours  definition
#define OLED_WHITE  0
#define OLED_BLACK 1
#define OLED_INVERSE 2

/* CH1115 Command Set*/
// Fundamental Commands
#define ERMCH1115_ENTIRE_DISPLAY_ON 0xA4 /**< Forcibly turns the entire display on regardless of the contents of the display data RAM */
#define ERMCH1115_ENTIRE_DISPLAY_OFF 0xA5 /**< Forcibly turns the entire display on regardless of the contents of the display data RAM */
#define ERMCH1115_DISPLAY_ON 0xAF /**< Turns on Display */
#define ERMCH1115_DISPLAY_OFF 0xAE /**< Turns off Display */
#define ERMCH1115_DISPLAY_NORMAL 0xA6  /**< Display  Inversion off*/
#define ERMCH1115_DISPLAY_INVERT 0xA7  /**< Display  Inversion on*/
#define ERMCH115_CONTRAST_CONTROL 0x81 /**<  Contrast Control Mode Set */
#define ERMCH115_CONTRAST_DATA_DEFAULT 0x80  /**<  Contrast Data Reg Set 0x00 to 0xFF */

// Addressing Setting Commands
#define ERMCH1115_SET_PAGEADD 0xB0 /**< Set Page Address: (B0H - B7H) */
#define ERMCH1115_SET_COLADD_LSB 0x00 /**< Set Lower Column Address: (00H - 0FH) */
#define ERMCH1115_SET_COLADD_MSB 0x10 /**< Set Higher Column Address: (10H – 1FH) */
#define ERMCH115_SET_DISPLAY_START_LINE 0x40 /**< Determine the initial display line */

// Hardware Configuration Commands
#define ERMCH1115_SET_PUMP_REG 0x30 /**< Output voltage (V PP ) internal charger pump. */
#define ERMCH115_SET_PUMP_SET   0x01 /**<  A1:A0[] 01 = 7.4v  */
#define ERMCH1115_IREF_REG 0x82 /**< I REF Resistor Set  */
#define ERMCH1115_IREF_SET 0x00 /**< I REF Resistor adjust */
#define ERMCH1115_SEG_SET_REMAP  0xA0 /**< Set Segment Re-map: (A0H - A1H) */
#define ERMCH1115_SEG_SET_PADS 0xA2 /**<Set SEG pads hw config: (A2H – A3H) */
#define ERMCH1115_MULTIPLEX_MODE_SET 0xA8 /**<Multiplex Ration Mode Set */
#define ERMCH1115_MULTIPLEX_DATA_SET  0x3F /**<Multiplex Ration Data Set: (00H - 3FH) */

#define ERMCH1115_DC_MODE_SET 0xAD /**< DC-DC Control Mode Set */
#define ERMCH1115_DC_ONOFF_SET 0x8B /**< DC-DC ON/OFF Mode Set (8AH - 8BH) (a=off; b=on) */
#define ERMCH1115_COMMON_SCAN_DIR 0xC0 /**< Set Common Op Scan Dir:C0H - C8H Flip vertical */
#define ERMCH1115_OFFSET_MODE_SET 0xD3 /**<Display Offset Mode Set: */
#define ERMCH1115_OFFSET_DATA_SET 0x00 /**<Display Offset Data Set: (00H~3FH) */
#define ERMCCH1115_BREATHEFFECT_SET 0x23 /**< Set Breathing Display Effect: */
#define ERMCCH1115_BREATHEFFECT_DATA 0x81 /**< Display Effect ON/OFF and Time Interval: */

// Timing & Driving Scheme Setting Commands
#define ERMCH1115_OSC_FREQ_MODE_SET 0xD5 /**<Divide Ratio/Oscillator Frequency Mode Set: (D5H) */
#define ERMCH1115_OSC_FREQ_DATA_SET 0xA0  /**<Divide Ratio/Oscillator Frequency Data Set: */
#define ERMCH1115_PRECHARGE_MODE_SET 0xD9 /**<Pre-charge Period Mode Set: */
#define ERMCH1115_PRECHARGE_DATA_SET 0x22 /**<Discharge/Pre-charge Period Data Set: (00H - FFH) */
#define ERMCH1115_COM_LEVEL_MODE_SET 0xDB /**<COM Deselect Level Mode Set: (DBH) */
#define ERMCH1115_COM_LEVEL_DATA_SET 0x40 /**<VCOM Deselect Level Data Set: (00H - FFH) */


// HORIZONTAL Scrolling Commands
#define ERMCH1115_HORIZONTAL_A_SCROLL_SETUP 0x24 /**<  Additional Horizontal Scroll Setup Mode Set: (24H) */
#define ERMCH1115_HORIZONTAL_A_SCROLL_SET_SCOL 0x00  /**< Start Column Position Set: (A7 – A0) */
#define ERMCH1115_HORIZONTAL_A_SCROLL_SET_ECOL 0x7F /**< End Column Position Set: (B7 – B0) */
#define ERMCH1115_SCROLL_SETUP  0x26 /**<Horizontal Scroll Setup: 26 right 27 left (A2 – A0)*/
#define ERMCH1115_SPAGE_ADR_SET 0x00  /**< Start Page Address Set 0x00 = page 0 */
#define ERMCH1115_TIME_SET 0x00 /**<Time Interval Set: (B2 – B0) 0x00 = 6 frames */
#define ERMCH1115_EPAGE_ADR_SET  0x07 /**<End Page Address Set: (C2 – C0)  */
#define ERMCH1115_SET_SCROLL_MODE 0x28 /**< Set Scroll Mode: (28H – 2BH) 0x28 = continuous */
#define ERMCH1115_DEACTIVATE_SCROLL  0x2E /**< De-active Scroll mode */
#define ERMCH1115_ACTIVATE_SCROLL   0x2F /**<active Scroll mode */

// GPIO abstraction
#define ERMCH1115_CS_SetHigh digitalWrite(_OLED_CS, HIGH)
#define ERMCH1115_CS_SetLow digitalWrite(_OLED_CS, LOW)
#define ERMCH1115_CD_SetHigh digitalWrite(_OLED_CD, HIGH)
#define ERMCH1115_CD_SetLow digitalWrite(_OLED_CD, LOW)
#define ERMCH1115_RST_SetHigh digitalWrite(_OLED_RST, HIGH)
#define ERMCH1115_RST_SetLow digitalWrite(_OLED_RST, LOW)
#define ERMCH1115_SCLK_SetHigh digitalWrite(_OLED_SCLK, HIGH) // SW SPI only last four lines
#define ERMCH1115_SCLK_SetLow  digitalWrite(_OLED_SCLK, LOW) 
#define ERMCH1115_SDA_SetHigh digitalWrite(_OLED_DIN, HIGH)
#define ERMCH1115_SDA_SetLow  digitalWrite(_OLED_DIN,LOW)

// Delays
#define ERMCH1115_INITDELAY 100 /**< mS delay set after init and before operations */
#define ERMCH1115_HIGHFREQ_DELAY 0 /**< uS  delay, Can be used in software SPI for high freq MCU*/
#define ERMCH1115_RST_DELAY1 10 /**< mS delay , used in reset routine  */
#define ERMCH1115_RST_DELAY2 100 /**< mS delay , used in reset routine */

// SPI
#define SPI_FREQ 8000000 /**< Mhz SPI bus baud rate  */
#define SPI_DIRECTION  MSBFIRST  /**< SPI data bit order orientation */
#define SPI_ERMCH1115_MODE SPI_MODE0 /**< SPI Mode 0-3 */
#define SPI_ERMCH1115_CLOCK_DIV SPI_CLOCK_DIV8  /**< SPI bus baud rate  ,STM32 data use only */

//There is a pre-defined macro SPI_HAS_TRANSACTION in SPI library for checking 
 //whether the firmware of the Arduino board supports SPI.beginTransaction().
#ifdef SPI_HAS_TRANSACTION
	#define SPI_TRANSACTION_START SPI.beginTransaction(SPISettings(SPI_FREQ, SPI_DIRECTION, SPI_ERMCH1115_MODE)); 
	#define SPI_TRANSACTION_END SPI.endTransaction();                
#else // SPI transactions likewise not present in MCU or lib
	#define SPI_TRANSACTION_START SPI.setClockDivider(SPI_ERMCH1115_CLOCK_DIV); // 72/8 = 9Mhz
	#define SPI_TRANSACTION_END  // Blank
#endif

const uint8_t ERMCH1115_SCREEN_WIDTH = 128; /**< Width of screen in pixels */
const uint8_t ERMCH1115_SCREEN_HEIGHT = 64; /**< Height of screen in pixels */

// ** CLASS SECTION **

/*! @brief class to hold screen data to define buffer , multiple screens can be made for the shared buffer
    Buffer must be same size and offsets to if saving Data memory is goal */
class  ERMCH1115_SharedBuffer
{
	public :
		ERMCH1115_SharedBuffer(uint8_t* mybuffer, uint8_t w,  uint8_t h, int16_t  x, int16_t y) ;
		~ERMCH1115_SharedBuffer(){};
		
		uint8_t* screenBuffer; /**<  pointer to shared buffer screen  data */
		uint8_t width;   /**< buffer x size in pixels  */
		uint8_t height; /**< buffer y size */
		int16_t xoffset; /**< x offset */
		int16_t yoffset; /**< y offset */
	private:
};

/*! @brief class to drive the ERMCh1115 OLED */
class ERMCH1115 : public ERMCH1115_graphics  {
  public:
	ERMCH1115(int8_t cd, int8_t rst, int8_t cs, int8_t sclk, int8_t din);
	ERMCH1115(int8_t cd, int8_t rst, int8_t cs);

	~ERMCH1115(){};
	
		virtual void drawPixel(int16_t x, int16_t y, uint8_t colour) override;
	void OLEDupdate(void);
	void OLEDclearBuffer(void);
	void OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data);

	void OLEDbegin(uint8_t OLEDcontrast = ERMCH115_CONTRAST_DATA_DEFAULT);
	void OLEDinit(void);
	void OLEDReset(void);
	
	void OLEDFillScreen(uint8_t pixel, uint8_t mircodelay);
	void OLEDFillPage(uint8_t page_num, uint8_t pixels,uint8_t delay);
	void OLEDBitmap(int16_t x, int16_t y, uint8_t w, uint8_t h, const uint8_t* data);
	
	void OLEDEnable(uint8_t on);
	void OLEDInvert(uint8_t on);
	void OLEDFlip(uint8_t on);
	void OLEDContrast(uint8_t contrast = ERMCH115_CONTRAST_DATA_DEFAULT);
	void OLEDscroll(uint8_t bits) ;
	void OLEDscrollSetup(uint8_t Timeinterval= ERMCH1115_TIME_SET, uint8_t Direction=ERMCH1115_SCROLL_SETUP, uint8_t mode=ERMCH1115_SET_SCROLL_MODE) ;
	void OLEDfadeEffect(uint8_t bits = ERMCCH1115_BREATHEFFECT_DATA);
	bool OLEDIssleeping(void);
	void OLEDPowerDown(void);
	
	ERMCH1115_SharedBuffer* ActiveBufferPtr=nullptr; /**< Active buffer pointer , a pointer to which shared buffer object */

  private:

	void send_data(uint8_t data);
	void send_command(uint8_t command, uint8_t value);
	bool isHardwareSPI(void);
	void CustomshiftOut(uint8_t bitOrder, uint8_t val);

	int8_t _OLED_CS;   /**< GPIOChip select  line */
	int8_t _OLED_CD;   /**< GPIO Data or command line */
	int8_t _OLED_RST;  /**< GPIO Reset line */
	int8_t _OLED_SCLK; /**< GPIO Clock Line Software SPI only*/
	int8_t _OLED_DIN;   /**< GPIO MOSI Line Software SPI only*/

	bool _sleep = true; /**< False awake/ON , true sleep/OFF */
	uint8_t _OLEDcontrast; /**< Contrast default 0x80 datasheet 00-FF */

}; 

#endif // end of guard header

