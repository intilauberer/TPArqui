
#include <naiveConsole.h>
#include "syscall.h"
#include "drivers/include/videoDriver.h"
#include "include/defs.h"
#define BUFSIZE 4096

extern int getKey();


void sys_write(const char *buf, int len, int filedescriptor){
    if(filedescriptor == 1){
        drawWord(buf);
        return;
    }
    if(filedescriptor == 2){
        drawWordColor(RED, buf);
    }
    return;
}

// char getchar(){
//     char c = getKey();
//     if (c != 0) {
//         character(c);
//     }
//     return c;
// }

// void getCommand(char * buf, int len){
//     int i = 0;
//     char c = 0;
//     while ((c = getchar()) && c != '\n' && i < len) {
//         buf[i] = c;
//         i++;
//     }
//     buf[i] = 0;
//     return;
// }

// void sys_read(const char *buf, int len, int filedescriptor){
//     char buffer[BUFSIZE] = { NULL };
//     if (filedescriptor == 0){
//         getCommand(buffer, len);
//     }
// }