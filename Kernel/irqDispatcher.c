#include <time.h>
#include <stdint.h>
#include "syscall.h"
static void int_20();
static void int_21();
static uint64_t int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {

	void (*interruption[256])(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8);
	interruption[0]=&int_20;
	interruption[1]=&int_21;
	interruption[80]=&int_80;
	interruption[irq](rdi,rsi,rdx,rcx,r8);
	return;
}

void int_20() {
	timer_handler();
}

void int_21() {
	keyboard_handler();
}

uint64_t int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {

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