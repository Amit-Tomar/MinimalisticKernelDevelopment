#include "../interruptDescriptorTable.h"

/* Make a interrupt descriptor table with 256 entries. 256 entries are defined instead of 32 to handle situation
   when an undefined IDT entry is requested. We have set the 'presence' bit for these descriptor as 0. 
   This will cause an "Unhandled Interrupt" exception */

interruptDescriptor interruptDescriptorTable[256];
interruptDescriptorTableLoader idtLoader;

// Fill interrupt descriptor table
void fillInterruptDescriptorTable(unsigned char interruptNumber, unsigned long interruptDescriptorTableBaseAddress, unsigned short segmentSelector, unsigned char flags)
{    
    // Extract the lower 16 bits interruptDescriptorTableBaseAddress 
    interruptDescriptorTable[interruptNumber].interruptHandlerAddress_lower16bit  = (interruptDescriptorTableBaseAddress & 0xFFFF);
    // Extract the higher 16 bits interruptDescriptorTableBaseAddress 
    interruptDescriptorTable[interruptNumber].interruptHandlerAddress_higher16bit = (interruptDescriptorTableBaseAddress >> 16) & 0xFFFF;

	// Fill rest of the value in the table
    interruptDescriptorTable[interruptNumber].segmentSelector = segmentSelector;
    interruptDescriptorTable[interruptNumber].ignoreValueAsZero = 0;
    interruptDescriptorTable[interruptNumber].flags = flags | 0x60;
}

// Load and install the IDT
void loadAndInitializeIDT()
{
	// Initialize the IDTLoader with our custom IDT values
    idtLoader.interruptDescriptorTableLimit = MAX_INTERRUPT_DESCRIPTOR_TABLE_SIZE_LIMIT;
    idtLoader.interruptDescriptorTableBaseAddress = (interruptDescriptor *)&interruptDescriptorTable;    
    
    // Initialize the full Interrupt descriptor table with all 0s
    interruptDescriptor * ptr_idt_entry = (interruptDescriptor *)&interruptDescriptorTable ;    
    for( int i = 0 ; i < 256 ; ++ i )
    {
      ptr_idt_entry -> interruptHandlerAddress_lower16bit =  0 ;     
      ptr_idt_entry -> segmentSelector =  0 ;     
      ptr_idt_entry -> ignoreValueAsZero =  0 ;     
      ptr_idt_entry -> flags =  0 ;     
      ptr_idt_entry -> interruptHandlerAddress_higher16bit =  0 ;     
    }

	// Pass the control to IDT loader in Startup.asm
    asmf_loadInterruptDescriptorTable();
}
