#ifndef INTERRUPT_DESCRIPTOR_TABLE_H
#define INTERRUPT_DESCRIPTOR_TABLE_H

#include "utility.h"

#define MAX_INTERRUPT_DESCRIPTOR_TABLE_SIZE_LIMIT (sizeof (interruptDescriptor) * 256) - 1

//  Declared in entrypoint.asm and is used to initialize our IDT.S
extern void asmf_loadInterruptDescriptorTable();

// An entry in the interrupt descriptor table
typedef struct
{
    unsigned short interruptHandlerAddress_lower16bit;  	// Lower 16 bits of the Address to which control should be passed when interrupt occurs
    unsigned short segmentSelector;                     	// Kernel segment selector
    unsigned char  ignoreValueAsZero;     				    // Always selected as 0
    unsigned char  flags;       				            // IDT flags for different kinds of Interrupt gates
    unsigned short interruptHandlerAddress_higher16bit; 	// Higher 16 bits of the Address to which control should be passed when interrupt occurs
}__attribute__((packed))

 interruptDescriptor ;

// Special format required by LIDT instruction to load the Interrupt descriptor table
typedef struct 
{
    unsigned short interruptDescriptorTableLimit;
    unsigned int   interruptDescriptorTableBaseAddress;
} __attribute__((packed))
interruptDescriptorTableLoader ;

void fillInterruptDescriptorTable(unsigned char interruptNumber, unsigned long interruptDescriptorTableBaseAddress, unsigned short segmentSelector, unsigned char flags);
void loadAndInitializeIDT();

#endif
