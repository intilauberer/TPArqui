
#include <naiveConsole.h>
#include "syscall.h"
#include "drivers/include/videoDriver.h"
#include "include/defs.h"


extern int getKey();



void sys_write(const char *buf, int len, int filedescriptor){
    if(filedescriptor == 1){
        drawWord(buf);
        return;
    }
    if(filedescriptor == 2){
        drawWordColor(RED, buf);
        return;
    }
    invalidFd();
    return;
    
}

static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
'\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 
'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0, 0 }; //hay que sacarlo de aca

void sys_read( char *buf, int len, int filedescriptor){
    
    if (filedescriptor == 0){
        char aux;
        for(int i=0; i < len; ){
            _hlt();
            aux=getKey();
            if(aux>=0 && aux<=256){
                if(aux == '\b'){
                    backspace();
                }
                else{
                    buf[i++]=ScanCodes[aux];
                    character(WHITE, buf[i-1]);
                }
            }
            
        }
        character(RED, 'a'); //[DEBUG]
        return;
    }
    invalidFd();
    return;

}