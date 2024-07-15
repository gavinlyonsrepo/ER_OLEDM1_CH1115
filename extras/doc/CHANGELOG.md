# Changelog

* version 1.0.0 May 2021
	* first release
* Version 1.3.0 Feb 2022
	* drawBitmap() function is now set up for both horizontal and vertical addressed bitmap data,
	  Vertical is default. The addressing mode is changed by setDrawBitmapAddr(), new function.  
	* Enum added for font name labels instead of raw numbers, 
	  This will cause font compiler warnings for sketch's written on versions before 1.3.0 , 
	  The sketch's will still compile and work,
	  Simply replace font numbers  with the relevant enum text labels to get rid of warnings. 
	* A new function added for initialising a multibuffer struct , OLEDinitBufferStruct(),
	  backward compatible with old manual workflow.  
* Version 1.3.1 Sep 2022
	* Minor update
	* Fixed typo in example file ER_OLEDM1_CH1115_MBUF.ino  Line 42 
	* read: myOLED.setFontNum(1); changed it to: myOLED.setFontNum(CH1115Font_Default);
	* This typo would just cause compiler warnings on most boards but on some MCU would cause a compile error.
* Version 1.3.2 December 2022
	* Three new fonts added (tiny, homespun + mednum)
	* new method "drawText" added
	* Font data placed in .cpp file 
	* .h files changed to .hpp
* Version 1.3.3 May 2023
	* Added Doxygen style comments to create automated API
	* Replaced multi-screen struct with a class 
	* Added Enum font inside class name space
	* Removed no buffer mode.
* Version 1.4.0 Jan 2024
	* OLED width & height no longer constant, and must now be supplied in constructor.
	* SW SPI GPIO delay can now be modified by a setter function
	* Enhanced Error handling for fonts and bitmaps, enum  *CH1115_Return_codes* added.
	* Fonts 9-12 added
	* Fonts 7-8 characters increased from 11 to 14.
* Version 1.4.1 Feb 2024
	* Minor update.
	* PROGMEM keyword added to font 12(which was added in 1.4.0
	* DrawPixel method boundary scan adjusted so 90 and 270 degree rotation is 
		calibrated for whole screen not shared screen mode.
* Version 1.4.2 June 2024 
	* Minor update. Add back in pgm_read_byte command as it was removed on last update
	so library works fully with UNO rev3.0