#include "../utility.h"
#include "../displayDriver.h"
#include "../interruptRequests.h"
#include "../timerHandler.h"

int totalSystemTicks = 0;
int totalTimeInSeconds = 0;
int timer_tick_request = -1;
int requestPending = 0 ;

void initialize_Timer()
{
	/*unsigned long int frequencyOfTimer = 18.2 ;
	int divisor = frequencyOfTimer;  
	     		  
    writeByteToPort (0x43, 0x36);             // Sending command byte
    writeByteToPort (0x40, divisor & 0xFF);   // Set low byte of divisor
    writeByteToPort (0x40, divisor >> 8);     // Set high byte of divisor*/
}

void timerInterruptHandlingRoutine(registerStructure *r)
{
    totalSystemTicks++;

	// 18.02 Hz is the default firing frequency of timer interrupts
    if (totalSystemTicks % 18 == 0 && 1 == requestPending)
    {      
        totalTimeInSeconds ++ ;
        setTextColor(eCyan);
        putStringOnScreen("\nTimer triggered.");
	
		if( timer_tick_request == totalTimeInSeconds )
		{
		  putStringOnScreen("\nTimer expired.\n");
		  requestPending = 0 ;          
		}
    }
}

void startTimer(unsigned int time)
{
    timer_tick_request = time + totalTimeInSeconds ;
    requestPending = 1;
    setTextColor(eWhite);
    putStringOnScreen("\n\nStart timer requested. \n");
}

