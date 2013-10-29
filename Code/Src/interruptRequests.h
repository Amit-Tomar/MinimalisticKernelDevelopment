#ifndef INTERRUPT_REQUEST_H
#define INTERRUPT_REQUEST_H

#include "utility.h"

#define MASTER_PIC_COMMAND_REGISTER_IO_PORT 0x20
#define MASTER_DATA    						0x21
#define SLAVE_PIC_COMMAND_REGISTER_IO_PORT  0xA0
#define SLAVE_DATA     						0xA1
#define END_OF_INTERRUPT 					0x20

void common_interruptRequestServiceRoutine(registerStructure *);
void initialize_interruptRequestService();

#endif
