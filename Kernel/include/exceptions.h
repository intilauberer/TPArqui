#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "include/registers.h"
void exceptionDispatcher(int exception, registerStructT * registers);

static void zero_division();
static void invalid_opcode();
#endif