#include "../utility.h"
#include "../keyBoardHandler.h"
#include "../displayDriver.h"
#include "../interruptRequests.h"
#include "../timerHandler.h"
#include "../timerHandler.h"

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
	   0,	// Left Shift
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

void handleKeyPress(registerStructure *registerInformation)
{
   unsigned char keyPressed ;   
   unsigned short port = 0x60;
   
   // Read the value from data register
   __asm__ __volatile__ ("inb %1, %0" : "=a" (keyPressed) : "dN" (port));

    // When a key is released, highest byte is set to 1
    if ( 1 == (keyPressed & 0x80))
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    
    // Key pressed
    else
    {
        /* You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        
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
