

#include "exceptions.h"
#include "drivers/include/videoDriver.h"


#define ZERO_EXCEPTION_ID 0
void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
		return;
	}
	invalid_opcode();
	
}

static void zero_division() {
	drawWordColor(RED, "FATAL ERROR:No se puede dividir por 0");
	newline();
}

static void invalid_opcode() {
	drawWordColor(RED, "FATAL ERROR:Invalid opcode");
	newline()
}