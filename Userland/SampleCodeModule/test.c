#include <stdio.h>
#include "utils.h"
#include "UserSyscalls.h"

void div0(){

    int a = 1;
    int b = 0;
    int c = a/b;

    // char a[10];
    // char b[10];
    // own_scanf("%s %s", &a, &b);
    // call_sys_write(a, 10, STDERR);
    // call_sys_write("\n", 1, STDERR);
    // call_sys_write(b, 10, STDERR);

    
    //putC(a);
    //int c = b/a;
    // char c = getC();
    // putC(c);



    return;
}