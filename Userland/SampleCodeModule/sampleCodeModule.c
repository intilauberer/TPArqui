/* sampleCodeModule.c */
#include "UserSyscalls.h"
#include "shell.h"
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;
extern void test(void);
void div0();
int main() {
	//All the following code may be removed 
	
	*v = 'X';
	*(v+1) = 0x74;
	// test();
	__shell_init__();
	char buff[5000];
	// test();
	// char buff[10];
	// call_sys_read(buff, 10, 0);
	call_sys_read(buff, 5000,0);
	// div0();
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}