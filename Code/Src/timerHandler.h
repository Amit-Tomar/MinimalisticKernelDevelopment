#ifndef timerInterruptHandlingRoutine_H
#define timerInterruptHandlingRoutine_H

#include "utility.h"

void timerInterruptHandlingRoutine(registerStructure *r);
void initialize_Timer();
void startTimer(unsigned int);

#endif
