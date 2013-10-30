#include "../utility.h"
#include "../displayDriver.h"
#include "../interruptRequests.h"
#include "../interruptDescriptorTable.h"
#include "../keyBoardHandler.h"
#include "../timerHandler.h"

extern void stub_interruptRequestServiceRoutine0();
extern void stub_interruptRequestServiceRoutine1();
extern void stub_interruptRequestServiceRoutine2();
extern void stub_interruptRequestServiceRoutine3();
extern void stub_interruptRequestServiceRoutine4();
extern void stub_interruptRequestServiceRoutine5();
extern void stub_interruptRequestServiceRoutine6();
extern void stub_interruptRequestServiceRoutine7();
extern void stub_interruptRequestServiceRoutine8();
extern void stub_interruptRequestServiceRoutine9();
extern void stub_interruptRequestServiceRoutine10();
extern void stub_interruptRequestServiceRoutine11();
extern void stub_interruptRequestServiceRoutine12();
extern void stub_interruptRequestServiceRoutine13();
extern void stub_interruptRequestServiceRoutine14();
extern void stub_interruptRequestServiceRoutine15();

// Re map the interruptRequestService and fill in the IDT with more values
void initialize_interruptRequestService()
{
	// Remap the interruptRequestService by sending commands to the Programmable Interrupt Controller 
	// to make IRQ 0 to 15 be remapped to IDT entries 32 to 47
	
	writeByteToPort(0x20, 0x11);
    writeByteToPort(0xA0, 0x11);
    writeByteToPort(0x21, 0x20);
    writeByteToPort(0xA1, 0x28);
    writeByteToPort(0x21, 0x04);
    writeByteToPort(0xA1, 0x02);
    writeByteToPort(0x21, 0x01);
    writeByteToPort(0xA1, 0x01);
    writeByteToPort(0x21, 0x0);
    writeByteToPort(0xA1, 0x0);   
    
    // Fill in the appropriate handlers in IDT	
	
    fillInterruptDescriptorTable(32, (unsigned)stub_interruptRequestServiceRoutine0,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(33, (unsigned)stub_interruptRequestServiceRoutine1,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(34, (unsigned)stub_interruptRequestServiceRoutine2,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(35, (unsigned)stub_interruptRequestServiceRoutine3,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(36, (unsigned)stub_interruptRequestServiceRoutine4,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(37, (unsigned)stub_interruptRequestServiceRoutine5,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(38, (unsigned)stub_interruptRequestServiceRoutine6,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(39, (unsigned)stub_interruptRequestServiceRoutine7,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(40, (unsigned)stub_interruptRequestServiceRoutine8,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(41, (unsigned)stub_interruptRequestServiceRoutine9,  CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(42, (unsigned)stub_interruptRequestServiceRoutine10, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(43, (unsigned)stub_interruptRequestServiceRoutine11, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(44, (unsigned)stub_interruptRequestServiceRoutine12, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(45, (unsigned)stub_interruptRequestServiceRoutine13, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(46, (unsigned)stub_interruptRequestServiceRoutine14, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(47, (unsigned)stub_interruptRequestServiceRoutine15, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
}

// Handle the interrupt request by this common service routine and then inform the IRQ Controllers about the same.
void common_interruptRequestServiceRoutine(registerStructure * registerInformation)
{
    // Handle by appropriate function
    
    // putStringOnScreen("\nIRQ received\n");
    
    asm volatile("cli");
            
    if ( 32 == registerInformation->interruptNumber)
    {
        timerInterruptHandlingRoutine(registerInformation);
    }
    
    else if ( 33 == registerInformation->interruptNumber )
    {
		handleKeyPress(registerInformation);				
	}

    /* If the IDT entry that was invoked was greater than 40 ( IRQ8 - IRQ15), 
     * then we need to send an EOI to the slave controller */
    if (registerInformation->interruptNumber >= 40)
    {
        writeByteToPort(SLAVE_PIC_COMMAND_REGISTER_IO_PORT, END_OF_INTERRUPT);
    }

    // Master controller is to be notified always
    writeByteToPort(MASTER_PIC_COMMAND_REGISTER_IO_PORT, END_OF_INTERRUPT 	);
    
      asm volatile("sti");

}
