#include "../displayDriver.h"
#include "../utility.h"

// Screen is in the text mode and of the size 
// MAX_CHARACTERS_IN_ROW characters (80) x MAX_CHARACTERS_IN_COLUMN (25) characters

textColor foregroundColor;
textColor backgroundColor;

unsigned int currentCursorPosition_X;
unsigned int currentCursorPosition_Y;

unsigned short * ptr_FRAME_BUFFER ;

// Write a byte out to the specified port.
void writeByteToPort(unsigned short portNumber, unsigned char value)
{
	// Inline assembly instruction as per data sheet
    asm volatile ("outb %1, %0" : : "dN" (portNumber), "a" (value));
}

// This function is used to read a byte from specified port
unsigned char readByteFromPort(unsigned short portNumber)
{
   unsigned char readByte;
   // Inline assembly instruction as per data sheet
   asm volatile("inb %1, %0" : "=a" (readByte) : "dN" (portNumber));
   return readByte;		
}

// This function is used to clear the screen .
void clearScreen () 
{
   unsigned short bytesToWrite = getBytesToWrite( ' ' , eBlack, eWhite );

   for (int i = 0; i < MAX_CHARACTERS_IN_ROW*MAX_CHARACTERS_IN_COLUMN; i++)
   {
       ptr_FRAME_BUFFER [i] = bytesToWrite;
   }

   // Move the hardware cursor back to the start.
   currentCursorPosition_X = 0;
   currentCursorPosition_Y = 0;
   
   moveCursorToLastPrintedCharacter();   
}

// This function is used to put a given string on the screen at the current position of the cursor .
void putStringOnScreen ( const char * string )
{ 
    if( 0 != string )
    {
        int i = 0;
		while ( '\0' != string[i] )
		{
		  putCharacterOnScreen(string[i]);
		  ++ i;
		}	  
    }
}

// This function is used to put a given character on the screen at the current position of the cursor .
void putCharacterOnScreen ( unsigned char c ) 
{
   unsigned short bytesToWrite = getBytesToWrite( c , backgroundColor, foregroundColor );

   // Handle newline 
   if ( '\n' == c )
   {
       currentCursorPosition_X = 0;
       currentCursorPosition_Y++;
   }
   
   else if ( '\b' == c || 0x08 == c )
   {
	   if( 0 != currentCursorPosition_X )
			-- currentCursorPosition_X;
	   else 
	   {
			-- currentCursorPosition_Y;
			currentCursorPosition_X = MAX_CHARACTERS_IN_ROW - 1 ;
	   }
	   
	   bytesToWrite = getBytesToWrite( ' ', eBlack, eWhite );
	   unsigned short frameBufferOffset = (currentCursorPosition_Y*MAX_CHARACTERS_IN_ROW) + currentCursorPosition_X;
       *(ptr_FRAME_BUFFER+frameBufferOffset) = bytesToWrite ;
   }
   
   // Handle all other characters
   else 
   {
       unsigned short frameBufferOffset = (currentCursorPosition_Y*MAX_CHARACTERS_IN_ROW) + currentCursorPosition_X;
       *(ptr_FRAME_BUFFER+frameBufferOffset) = bytesToWrite ;
       currentCursorPosition_X++;
   }

   // If we reach the end of line, move to next line
   if (currentCursorPosition_X >= MAX_CHARACTERS_IN_ROW)
   {
       currentCursorPosition_X = 0;
       currentCursorPosition_Y ++;
   }   
   
   // Scroll the screen and update cursor
   scrollDownScreen();
   moveCursorToLastPrintedCharacter();
}

// This function is used to set the text color for all the subsequent characters to be printed .
void setTextColor ( textColor color ) 
{
    foregroundColor = color ;
}

// This function is used to set the text background color for all the subsequent characters to be printed .
void setTextBackgroundColor ( textColor color ) 
{
    backgroundColor = color ;
}

/* This function is used to initialize any particular settings related to graphics driver , before we begin printing the text .
It is to be called first thing before trying to begin anything on the scren */
void initializeGraphicsDriver () 
{
      foregroundColor = eWhite;
      backgroundColor = eBlack;
      currentCursorPosition_X = 0;
      currentCursorPosition_Y = 0;
      ptr_FRAME_BUFFER = (unsigned short *)FRAME_BUFFER_ADDRESS;
      clearScreen();
}

// This function is used to update the cursor position on screen after printing a character .
void moveCursorToLastPrintedCharacter ()
{
   unsigned short currentCursorOffset = (currentCursorPosition_Y * MAX_CHARACTERS_IN_ROW) + currentCursorPosition_X ;   
   
   // Informing VGA before setting the higher byte
   writeByteToPort(VGA_COMMAND_PORT, HIGH_BYTE_FLAG);         
   // Set the higher byte
   writeByteToPort(VGA_INPUT_PORT, currentCursorOffset >> 8); 
   
   // Informing VGA before setting the higher byte
   writeByteToPort(VGA_COMMAND_PORT, LOW_BYTE_FLAG);
   // Set the higher byte
   writeByteToPort(VGA_INPUT_PORT, currentCursorOffset); 
}

// This function is used to scroll down the screen .
void scrollDownScreen ()
{   
   unsigned short bytesToWrite = getBytesToWrite( ' ' , eBlack, eWhite );

   // Row MAX_CHARACTERS_IN_COLUMN is the end, this means we need to scroll up
   if(currentCursorPosition_Y >= MAX_CHARACTERS_IN_COLUMN)
   {
       for (int i = 0; i < (MAX_CHARACTERS_IN_COLUMN-1) *MAX_CHARACTERS_IN_ROW; i++)
       {
           ptr_FRAME_BUFFER [i] = ptr_FRAME_BUFFER[i+MAX_CHARACTERS_IN_ROW];
       }

	   // Draw blank line
       for (int i = (MAX_CHARACTERS_IN_COLUMN-1)*MAX_CHARACTERS_IN_ROW; i < MAX_CHARACTERS_IN_COLUMN*MAX_CHARACTERS_IN_ROW; i++)
       {
          ptr_FRAME_BUFFER [i] = bytesToWrite;
       }
       // Move cursor to last line
       currentCursorPosition_Y = (MAX_CHARACTERS_IN_COLUMN-1);
   }
}

// Get an appropriate byte to write based on the character, background and foreground colors
unsigned short getBytesToWrite ( char c , textColor bgColor, textColor fgColor ) 
{
    unsigned char higherByte = ( bgColor << 4 ) | (fgColor ) ;
    unsigned char lowerByte  = c  ;

    unsigned short higherByteAs16bitValue = higherByte  ;
    higherByteAs16bitValue = higherByteAs16bitValue << 8 ;

    unsigned short lowerByteAs16bitValue = lowerByte | 0 ;

    unsigned short complete16bitValue = higherByteAs16bitValue | lowerByteAs16bitValue ;

    return complete16bitValue;
}
