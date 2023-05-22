#include <stdio.h>

void div0(){
    int a = 0;
    int b = 1;
    int c = b/a;
    return;
}