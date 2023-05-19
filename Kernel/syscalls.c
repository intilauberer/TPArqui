
#include <naiveConsole.h>
#include "syscall.h"
#include "drivers/include/videoDriver.h"

void sys_write(const char *buf, int len, int filedescriptior){
    if(filedescriptior == 1){
        drawWord(buf);
    }else if(filedescriptior == 2){
        drawWordColor(buf, RED);
    }
}