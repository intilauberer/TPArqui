

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

	
}

static void zero_division() {
	saveState();
	flag_snapshot_taken = 1;
	drawWordColor(RED, "FATAL ERROR:No se puede dividir por 0");
	newline();
	// destroy_stack();
}

static void invalid_opcode() {
	saveState();
	flag_snapshot_taken = 1;
	drawWordColor(RED, "FATAL ERROR:Invalid opcode");
	newline();
	// destroy_stack();
}