/* sampleCodeModule.c */
#include <UserSyscalls.h>
#include <shell.h>
char * v = (char*)0xB8000 + 79 * 2;
static int var1 = 0;
static int var2 = 0;
int main() {
	//All the following code may be removed 
	
	*v = 'X';
	*(v+1) = 0x74;
	__shell_init__();
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}