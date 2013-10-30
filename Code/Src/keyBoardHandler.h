#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#define KEYBOARD_DATA_REGISTER 0x60
#define LEFT_SHIFT -1

void initializeKeyboard();
void handleKeyPress(registerStructure *); 

#endif
