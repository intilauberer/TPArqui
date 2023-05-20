#include <time.h>
#include <stdint.h>
#include "syscall.h"
#include "include/defs.h"

static void int_20();
static void int_21();
static void int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);

typedef void (*InterruptHandler)(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
	InterruptHandler interruption[256] = {NULL};
	interruption[0]=&int_20;
	interruption[1]=&int_21;
	interruption[96]=&int_80;

    if (irq >= 0 && irq < 256 && interruption[irq] != NULL) {
        InterruptHandler handler = interruption[irq];
        handler(rdi, rsi, rdx, rcx, r8);
    }
}

void int_20() {
	timer_handler();
}

void int_21() {
	keyboard_handler();
}

void int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {

    switch (rdi)
	{
	case 1:
		sys_write((char*)rsi, rdx, rcx);
		break;
	
	case 2:
		// sys_read();
		break;
	}
	
}