

#include "include/exceptions.h"
#include "drivers/include/videoDriver.h"
#include "registers.h"

#define ZERO_EXCEPTION_ID 0
void exceptionDispatcher(int exception, registerStructT * registers) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	}
	else{
		invalid_opcode();
	}
	printRegisters(registers);
	drawWordColor(RED, "Press any key to continue");
	char c;
	sys_read(&c, 1, 0);
	

}

 void zero_division() {
	// saveState();
	flag_snapshot_taken = 1;
	drawWordColor(RED, "FATAL ERROR: No se puede dividir por 0");
	newline();
}

 void invalid_opcode() {
	// saveState();
	flag_snapshot_taken = 1;
	drawWordColor(RED, "FATAL ERROR: Invalid opcode");
	newline();
}