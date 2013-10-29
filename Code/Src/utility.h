#ifndef UTILITY_H
#define UTILITY_H

#define FLAG_VALUE  							0x8E
#define CODE_SEGMENT_INITIAL_VALUE			 	0x08
#define FRAME_BUFFER_ADDRESS 	   			  	0xB8000
#define VGA_COMMAND_PORT     	   				0x3D4
#define VGA_INPUT_PORT       	   				0x3D5
#define HIGH_BYTE_FLAG       	   				14
#define LOW_BYTE_FLAG              				15
#define MAX_CHARACTERS_IN_ROW      				80
#define MAX_CHARACTERS_IN_COLUMN   				25

typedef struct 
{
    unsigned int gs, fs, es, ds;      
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  
    unsigned int interruptNumber, err_code;    
    unsigned int eip, cs, eflags, useresp, ss;   
} registerStructure ;
	
#endif		
