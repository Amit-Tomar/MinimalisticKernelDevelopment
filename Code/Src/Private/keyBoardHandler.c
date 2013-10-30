#include "../utility.h"
#include "../keyBoardHandler.h"
#include "../displayDriver.h"
#include "../interruptRequests.h"
#include "../timerHandler.h"
#include "../timerHandler.h"

int SHIFT_ENABLED = 0;

unsigned char keyboardMapping[128] =
{
    0, 
    27,   // Esc
    '1', 
    '2', 
    '3', 
    '4', 
    '5', 
    '6', 
    '7', 
    '8',
    '9', 
    '0', 
    '-', 
    '=', 
    '\b',
    '\t',
     'q', 
     'w', 
     'e', 
     'r',	
     't', 
     'y', 
     'u', 
     'i', 
     'o', 
     'p', 
     '[', 
     ']', 
     '\n',
      0,		
     'a', 
     's', 
     'd', 
     'f', 
     'g', 
     'h', 
     'j', 
     'k', 
     'l', 
     ';',	
	 '\'', 
	 '`', 
	   LEFT_SHIFT,	
      '\\', 
      'z', 
      'x', 
      'c', 
      'v', 
      'b', 
      'n',	
      'm', 
      ',', 
      '.', 
      '/',
         0, // Right Shift
      '*',
		0,	// Left Alt
	  ' ',	// Space bar 
		0,	// Caps lock 
		0,	// F1
		0,  // F2 
		0,  // F3 
		0,  // F4 
		0,  // F5 
		0,  // F6 
		0,  // F7 
		0,  // F8 
		0,  // F9
		0,	// F10 
		0,	// 69 - Num lock
		0,	// Scroll Lock 
		0,	// Home key 
		0,	// Up Arrow 
		0,	// Page Up 
	  '-',
		0,	// Left Arrow 
		0,
		0,	// Right Arrow 
	  '+',
		0,	// End key
		0,	// Down Arrow 
		0,	// Page Down 
		0,	// Insert Key 
		0,	// Delete Key 
		0,  // Undefined 
		0,  // Undefined   
		0,  // Undefined
		0,	// F11 Key 
		0,	// F12 Key 
		0	// All other keys are undefined 
};	

unsigned char keyboardMappingWithShift[128] =
{
    0, 
    27,   // Esc
    '1', 
    '2', 
    '3', 
    '4', 
    '5', 
    '6', 
    '7', 
    '8',
    '9', 
    '0', 
    '-', 
    '=', 
    '\b',
    '\t',
     'q', 
     'w', 
     'e', 
     'r',	
     't', 
     'y', 
     'u', 
     'i', 
     'o', 
     'p', 
     '[', 
     ']', 
     '\n',
      0,		
     'A', 
     'S', 
     'D', 
     'F', 
     'G', 
     'H', 
     'J', 
     'K', 
     'L', 
     ';',	
	 '\'', 
	 '`', 
	   0,	// Left Shift
      '\\', 
      'Z', 
      'X', 
      'C', 
      'V', 
      'B', 
      'N',	
      'M', 
      ',', 
      '.', 
      '/',
         0, // Right Shift
      '*',
		0,	// Left Alt
	  ' ',	// Space bar 
		0,	// Caps lock 
		0,	// F1
		0,  // F2 
		0,  // F3 
		0,  // F4 
		0,  // F5 
		0,  // F6 
		0,  // F7 
		0,  // F8 
		0,  // F9
		0,	// F10 
		0,	// 69 - Num lock
		0,	// Scroll Lock 
		0,	// Home key 
		0,	// Up Arrow 
		0,	// Page Up 
	  '-',
		0,	// Left Arrow 
		0,
		0,	// Right Arrow 
	  '+',
		0,	// End key
		0,	// Down Arrow 
		0,	// Page Down 
		0,	// Insert Key 
		0,	// Delete Key 
		0,  // Undefined 
		0,  // Undefined   
		0,  // Undefined
		0,	// F11 Key 
		0,	// F12 Key 
		0	// All other keys are undefined 
};

// Handles the keyboard interrupt
void handleKeyPress(registerStructure *registerInformation)
{
   unsigned char keyPressed ;   
   unsigned short port = 0x60;
   
   // Read the value from data register
   asm volatile("inb %1, %0" : "=a" (keyPressed) : "dN" (port));

    // When a key is released, highest byte is set to 1
    if ( 0 != (keyPressed & 0x80))
    {
        // Handle shift/ctrl keys
        if( LEFT_SHIFT == keyboardMapping[keyPressed] )
		{
			SHIFT_ENABLED = 0 ;
		}
    }
    
    // Key pressed
    else
    {        
		if( LEFT_SHIFT == keyboardMapping[keyPressed] )
		{
			SHIFT_ENABLED = 1 ;
		}
		
		if( 1 == SHIFT_ENABLED && LEFT_SHIFT == keyboardMapping[keyPressed] )
			putCharacterOnScreen(keyboardMappingWithShift[keyPressed]);
		else
		    putCharacterOnScreen(keyboardMapping[keyPressed]);
	
		if( 't' == keyboardMapping[keyPressed])
			startTimer(3);  
		else if( 'e' == keyboardMapping[keyPressed])
		{
			setTextColor(eWhite);
			putStringOnScreen("\n\nTrying to divide 1 by 0.\n");	  
			int i = 1 / 0;
		}
    }
}

void initializeKeyboard()
{
    
}
