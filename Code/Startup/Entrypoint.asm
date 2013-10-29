MBOOT_PAGE_ALIGN    equ 1<<0       ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1       ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value

MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                       ; All instructions should be 32-bit.

[GLOBAL multiboot]              ; Make 'multiboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.

; -------------------------------------------------------------------------------------------

multiboot:
  dd  MBOOT_HEADER_MAGIC        ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file. This identifies the kernel as multiboot-compatible.
  dd  MBOOT_HEADER_FLAGS        ; How GRUB should load your file / settings
  dd  MBOOT_CHECKSUM            ; To ensure that the above values are correct
   
  ; These symbols are all defined by the linker. We use them to tell GRUB where the different sections of our kernel can be located. 
   
  dd  multiboot                 ; Location of this descriptor
  dd  code                      ; Start of kernel '.text' (code) section.
  dd  bss                       ; End of kernel '.data' section.
  dd  end                       ; End of kernel.
  dd  start                     ; Kernel entry point (initial EIP).

; -------------------------------------------------------------------------------------------

; Interrupt request service routines

%macro stub_interruptRequestServiceRoutine 2  
  global stub_interruptRequestServiceRoutine%1    ; Global declaration of the stub, %1 accesses the first parameter.
  
stub_interruptRequestServiceRoutine%1: 
    cli                                           ; Disable interrupts
    push byte 0                                   ; Push dummy error code for keeping the structure in sync
    push byte %2                                  ; Push the interrupt number + 32
    jmp common_stub_interruptRequestServiceRoutine
    ret
%endmacro

stub_interruptRequestServiceRoutine 0 , 32
stub_interruptRequestServiceRoutine 1 , 33
stub_interruptRequestServiceRoutine 2 , 34
stub_interruptRequestServiceRoutine 3 , 35 
stub_interruptRequestServiceRoutine 4 , 36
stub_interruptRequestServiceRoutine 5 , 37
stub_interruptRequestServiceRoutine 6 , 38
stub_interruptRequestServiceRoutine 7 , 39
stub_interruptRequestServiceRoutine 8 , 40
stub_interruptRequestServiceRoutine 9 , 41
stub_interruptRequestServiceRoutine 10 , 42
stub_interruptRequestServiceRoutine 11 , 43
stub_interruptRequestServiceRoutine 12 , 44
stub_interruptRequestServiceRoutine 13 , 45
stub_interruptRequestServiceRoutine 14 , 46
stub_interruptRequestServiceRoutine 15 , 47    

extern common_interruptRequestServiceRoutine

common_stub_interruptRequestServiceRoutine:

    ; Save all the important processor registers
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
 
	; Call the common interrupt request handler in C
    mov eax, common_interruptRequestServiceRoutine
    call eax

    ; Restore back the state
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret		
    
; -------------------------------------------------------------------------------------------
; Interrupt service routine stubs

; ISR stub function's global declarations and definitions

; A macro taking only one parameter as an input
%macro stub_interruptServiceRoutine 1  
  global stub_interruptServiceRoutine%1           ; Global declaration of the stub, %1 accesses the first parameter.
  
stub_interruptServiceRoutine%1: 
    cli                                           ; Disable interrupts
    push byte 0                                   ; Push dummy error code for keeping the structure in sync
    push byte %1                                  ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine
%endmacro

stub_interruptServiceRoutine 0
stub_interruptServiceRoutine 1
stub_interruptServiceRoutine 2 
stub_interruptServiceRoutine 3 
stub_interruptServiceRoutine 4
stub_interruptServiceRoutine 5 
stub_interruptServiceRoutine 6
stub_interruptServiceRoutine 7

stub_interruptServiceRoutine8: 
	global stub_interruptServiceRoutine8
    cli                                           ; Disable interrupts
    push byte 8                                   ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine

stub_interruptServiceRoutine 9

stub_interruptServiceRoutine10: 
	global stub_interruptServiceRoutine10
    cli                                           ; Disable interrupts
    push byte 10                                   ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine
    
stub_interruptServiceRoutine11: 
	global stub_interruptServiceRoutine11
    cli                                           ; Disable interrupts
    push byte 11                                   ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine
    
stub_interruptServiceRoutine12: 
	global stub_interruptServiceRoutine12
    cli                                           ; Disable interrupts
    push byte 12                                   ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine
    
stub_interruptServiceRoutine13: 
	global stub_interruptServiceRoutine13
    cli                                           ; Disable interrupts
    push byte 13                                   ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine
    
stub_interruptServiceRoutine14: 
	global stub_interruptServiceRoutine14
    cli                                           ; Disable interrupts
    push byte 14                                   ; Push the interrupt number
    jmp common_stub_interruptServiceRoutine


stub_interruptServiceRoutine 15
stub_interruptServiceRoutine 16
stub_interruptServiceRoutine 17
stub_interruptServiceRoutine 18
stub_interruptServiceRoutine 19
stub_interruptServiceRoutine 20
stub_interruptServiceRoutine 21
stub_interruptServiceRoutine 22
stub_interruptServiceRoutine 23
stub_interruptServiceRoutine 24
stub_interruptServiceRoutine 25
stub_interruptServiceRoutine 26
stub_interruptServiceRoutine 27
stub_interruptServiceRoutine 28
stub_interruptServiceRoutine 29
stub_interruptServiceRoutine 30
stub_interruptServiceRoutine 31
 

extern common_interruptServiceRoutine

; Common ISR stub to store the processor state before callign the interrupt handler.
common_stub_interruptServiceRoutine:
    
    ; Store all the important registers onto the stack
    pusha		   ; Special instruction to push all the important registers onto stack together. Pushes back the registers edi,esi,ebp,esp,ebx,edx,ecx,eax
    push ds
    push es
    push fs
    push gs    
    
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Extended Stack Pointer is a 32 bit value containing the top of stack address (more accurately the bottom of stack on X86!)
    push eax
    
    ; Call the common interrupt handler in C
    mov eax, common_interruptServiceRoutine
    call eax       

    ; Restores the stored stack frame.
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; Pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP and return from an interrupt. 
				   ; It pops these values off the stack and returns the processor to the state it was in originally.
        
; -------------------------------------------------------------------------------------------

; Custom IDT loading into the processor's IDT register

global asmf_loadInterruptDescriptorTable
extern idtLoader

asmf_loadInterruptDescriptorTable:

    lidt [idtLoader] ; Special instruction to load the IDT into processor's interrupt descriptor table register (IDTR).
    ret
; -------------------------------------------------------------------------------------------

 ; The entry point that the linker uses by default is the symbol with the name _start. If we dont specify
 ; _start and link with gcc, it automatically includes a _start routine. It performs several operations
 ; like setting up argc and argv etc. and at the end calls main(). Here we manually specify that start the 
 ; executable from here and then pass on he control to main function manually later on. */

 [GLOBAL start]

; Decleration of the main function of our main.c file
[EXTERN main]                   

start:
  
 ; Interrupts are disabled. If interrupts are left enabled, the timer will fire one pretty soon (~milliseconds probably).
 ; The processor will then check your interrupt descriptor table (IDT) for the correct action to take.
 ; If initialisation hasnt happened yet, it won't find the right action and instead cause a double fault.
 ; If the double fault is not handled in the IDT, you get a tripple fault, and the processor restarts.
 
  cli                           
  
 ; call our main() function.

  call main            
  
  ; JMP $ is used to keep the processor busy at this location. The $ is used to refer to the same location where the instruction starts. 
  ; That means that the instruction will jump to itself and thereby create an endless loop. Removing this instruction causes an exception.
  
  jmp $                       
