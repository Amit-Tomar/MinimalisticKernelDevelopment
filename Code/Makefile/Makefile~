# This Makefile will compile Entrypoint.asm and main.c and then link them together into a kernel executable. 
# It uses a linker script, linkerScript.ld, to position differnt entitites at correct locations in the executable.

kernel: ../Build/Entrypoint.o ../Build/main.o ../Build/displayDriver.o ../Build/interruptDescriptorTable.o ../Build/keyBoardHandler.o ../Build/interruptRequests.o  ../Build/interruptServiceRoutine.o ../Build/timerHandler.o ../Linker/linkerScript.ld
	@ ld -T ../Linker/linkerScript.ld ../Build/Entrypoint.o ../Build/interruptRequests.o ../Build/keyBoardHandler.o ../Build/interruptDescriptorTable.o ../Build/interruptServiceRoutine.o ../Build/timerHandler.o ../Build/main.o ../Build/displayDriver.o -o ../Build/kernel
	@echo Combing main.o, displayDriver.o, Entrypoint.o, interruptDescriptorTable.o,keyBoardHandler.o, interruptServiceRoutine.o, interruptRequests.o, timerHandler.o and interruptHandler.o into single elf using linkerScript..
	@echo Build ends..	
		
../Build/main.o : ../Src/main.c		
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/main.c -o ../Build/main.o 
		@echo Converting main.c to main.o

../Build/Entrypoint.o : ../Startup/Entrypoint.asm
		@ nasm -f elf ../Startup/Entrypoint.asm -o ../Build/Entrypoint.o
		@echo Build begins.. 		
		@echo Converting Entrypoint.asm to Entrypoint.o
		
../Build/displayDriver.o : ../Src/Private/displayDriver.c
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/Private/displayDriver.c -o ../Build/displayDriver.o
		@echo Converting displayDriver.c to displayDriver.o
		
../Build/interruptDescriptorTable.o : ../Src/Private/interruptDescriptorTable.c
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/Private/interruptDescriptorTable.c -o ../Build/interruptDescriptorTable.o
		@echo Converting interruptDescriptorTable.c to interruptDescriptorTable.o

../Build/interruptServiceRoutine.o : ../Src/Private/interruptServiceRoutine.c
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/Private/interruptServiceRoutine.c -o ../Build/interruptServiceRoutine.o
		@echo Converting interruptServiceRoutine.c to interruptServiceRoutine.o

../Build/interruptRequests.o : ../Src/Private/interruptRequests.c
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/Private/interruptRequests.c -o ../Build/interruptRequests.o
		@echo Converting interruptRequests.c to interruptRequests.o
		
../Build/timerHandler.o : ../Src/Private/timerHandler.c
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/Private/timerHandler.c -o ../Build/timerHandler.o
		@echo Converting timerHandler.c to timerHandler.o
		
../Build/keyBoardHandler.o : ../Src/Private/keyBoardHandler.c
		@ gcc -std=gnu99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c ../Src/Private/keyBoardHandler.c -o ../Build/keyBoardHandler.o
		@echo Converting keyBoardHandler.c to keyBoardHandler.o		
clean:
	@echo Cleaning begins. Removing .o and kernel files..
	@ -rm ../Build/*.o ../Build/kernel
	@echo Cleaning done..
