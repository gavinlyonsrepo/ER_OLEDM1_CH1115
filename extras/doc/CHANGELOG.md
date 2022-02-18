# Changelog

* version 1.0.0 May 2021
	* first release
* Version 1.1 June 2021
	* added four fonts.
* Version 1.3 Feb 2022
	* drawBitmap() function is now set up for both horizontal and vertical addressed bitmap data,
	 Vertical is default. The addressing mode is changed by setDrawBitmapAddr(), new function.  
	* Enum added for font name labels instead of raw numbers, This will cause font compiler warnings for sketch's written on versions before 1.3.0 , The sketch's will still compile and work,
	Simply replace font numbers  with the relevant enum text labels to get rid of warnings. 
	* A new function added for initialising a multibuffer struct , OLEDinitBufferStruct(),
	backward compatible with old manual workflow.  
