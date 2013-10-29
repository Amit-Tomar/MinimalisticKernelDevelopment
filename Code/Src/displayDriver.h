#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

typedef enum
{ 
  eBlack , 
  eBlue , 
  eGreen ,
  eCyan,
  eRed,
  eMagenta,
  eBrown,
  eLightGrey,
  eDarkGrey,
  eLightBlue,
  eLightGreen,
  eLightCyan,
  eLightRed,
  eLightMagenta,
  eLightBrown,
  eWhite
  
} textColor ;

// This function is used to write a byte to specified port
void writeByteToPort(unsigned short portNumber, unsigned char value);

// This function is used to read a byte from specified port
unsigned char readByteFromPort(unsigned short portNumber);

// This function is used to clear the screen .
void clearScreen () ;

// This function is used to put a given character on the screen at the current position of the cursor .
void putCharacterOnScreen ( unsigned char c ) ;

// This function is used to put a given string on the screen at the current position of the cursor .
void putStringOnScreen ( const char * string ) ;

// This function is used to set the text color for all the subsequent characters to be printed .
void setTextColor ( textColor color ) ;

// This function is used to set the text background color for all the subsequent characters to be printed .
void setTextBackgroundColor ( textColor color ) ;

// This function is used to initialize any particular settings related to graphics driver , before we begin printing the text .
void initializeGraphicsDriver () ;

// This function is used to update the cursor position on screen after printing a character .
void moveCursorToLastPrintedCharacter () ;

// This function is used to scroll down the screen .
void scrollDownScreen () ;

// This function returns a 16 bit value to be used for writing a character on VGA device
unsigned short getBytesToWrite ( char c , textColor bgColor, textColor fgColor ) ;

#endif
