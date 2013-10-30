#include "../utility.h"
#include "../displayDriver.h"
#include "../interruptServiceRoutine.h"
#include "../interruptDescriptorTable.h"

extern void stub_interruptServiceRoutine0();
extern void stub_interruptServiceRoutine1();
extern void stub_interruptServiceRoutine2();
extern void stub_interruptServiceRoutine3();
extern void stub_interruptServiceRoutine4();
extern void stub_interruptServiceRoutine5();
extern void stub_interruptServiceRoutine6();
extern void stub_interruptServiceRoutine7();
extern void stub_interruptServiceRoutine8();
extern void stub_interruptServiceRoutine9();
extern void stub_interruptServiceRoutine10();
extern void stub_interruptServiceRoutine11();
extern void stub_interruptServiceRoutine12();
extern void stub_interruptServiceRoutine13();
extern void stub_interruptServiceRoutine14();
extern void stub_interruptServiceRoutine15();
extern void stub_interruptServiceRoutine16();
extern void stub_interruptServiceRoutine17();
extern void stub_interruptServiceRoutine18();
extern void stub_interruptServiceRoutine19();
extern void stub_interruptServiceRoutine20();
extern void stub_interruptServiceRoutine21();
extern void stub_interruptServiceRoutine22();
extern void stub_interruptServiceRoutine23();
extern void stub_interruptServiceRoutine24();
extern void stub_interruptServiceRoutine25();
extern void stub_interruptServiceRoutine26();
extern void stub_interruptServiceRoutine27();
extern void stub_interruptServiceRoutine28();
extern void stub_interruptServiceRoutine29();
extern void stub_interruptServiceRoutine30();
extern void stub_interruptServiceRoutine31();

// Initializes all the interrupt service routines
void initialize_interruptServiceRoutine()
{
    fillInterruptDescriptorTable(0, (unsigned)stub_interruptServiceRoutine0,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(1, (unsigned)stub_interruptServiceRoutine1,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(2, (unsigned)stub_interruptServiceRoutine2,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(3, (unsigned)stub_interruptServiceRoutine3,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(4, (unsigned)stub_interruptServiceRoutine4,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(5, (unsigned)stub_interruptServiceRoutine5,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(6, (unsigned)stub_interruptServiceRoutine6,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(7, (unsigned)stub_interruptServiceRoutine7,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(8, (unsigned)stub_interruptServiceRoutine8,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(9, (unsigned)stub_interruptServiceRoutine9,   CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(10, (unsigned)stub_interruptServiceRoutine10, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(11, (unsigned)stub_interruptServiceRoutine11, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(12, (unsigned)stub_interruptServiceRoutine12, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(13, (unsigned)stub_interruptServiceRoutine13, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(14, (unsigned)stub_interruptServiceRoutine14, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(15, (unsigned)stub_interruptServiceRoutine15, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);

    fillInterruptDescriptorTable(16, (unsigned)stub_interruptServiceRoutine16, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(17, (unsigned)stub_interruptServiceRoutine17, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(18, (unsigned)stub_interruptServiceRoutine18, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(19, (unsigned)stub_interruptServiceRoutine19, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(20, (unsigned)stub_interruptServiceRoutine20, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(21, (unsigned)stub_interruptServiceRoutine21, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(22, (unsigned)stub_interruptServiceRoutine22, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(23, (unsigned)stub_interruptServiceRoutine23, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);

    fillInterruptDescriptorTable(24, (unsigned)stub_interruptServiceRoutine24, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(25, (unsigned)stub_interruptServiceRoutine25, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(26, (unsigned)stub_interruptServiceRoutine26, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(27, (unsigned)stub_interruptServiceRoutine27, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(28, (unsigned)stub_interruptServiceRoutine28, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(29, (unsigned)stub_interruptServiceRoutine29, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(30, (unsigned)stub_interruptServiceRoutine30, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
    fillInterruptDescriptorTable(31, (unsigned)stub_interruptServiceRoutine31, CODE_SEGMENT_INITIAL_VALUE, FLAG_VALUE);
}

unsigned char *exception_messages[] =
{
    "Division By Zero exception",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint  exception",
    "Into Detected Overflow exception",
    "Out of Bounds exception",
    "Invalid Opcode exception",
    "No Coprocessor exception",
    "Double Fault exception",
    "Coprocessor Segment Overrun exception",
    "Bad TSS exception",
    "Segment Not Present exception",
    "Stack Fault exception",
    "General Protection Fault exception",
    "Page Fault exception",
    "Unknown Interrupt", 
    "Coprocessor Fault",
    "Alignment Check exception",
    "Machine Check exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception"
};

// Common handler for all the interrupts generated
void common_interruptServiceRoutine(registerStructure *registerInformation)
{
    setTextColor(eRed);
    putStringOnScreen("\nAlert : EXCEPTION OCCURED \n");
    if (registerInformation->interruptNumber < 32)
    {    
        putStringOnScreen(exception_messages[registerInformation->interruptNumber]);
		putStringOnScreen("\nCan not recover from exception. System being halted.\n");
		setTextColor(eWhite);
		while(1);
    }
}
