# Changelog

* version 1.0.0 May 2021
	* first release
* Version 1.1.0 June 2021
	* added four fonts.
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