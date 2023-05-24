
#include <naiveConsole.h>
#include "syscall.h"
#include "drivers/include/videoDriver.h"
#include "include/defs.h"
#include "drivers/include/keyboard_driver.h"
#include "stdin.h"

extern int getKey();



void sys_write(const char *buf, int len, int filedescriptor){

    switch (filedescriptor){
        case STDOUT: drawWord(buf);
            return;
        case STDERR: drawWordColor(RED, buf);
            return;
        default: invalidFd();
    }
    
}

void sys_read( char *buf, int len, int filedescriptor){

    switch (filedescriptor){
        case STDIN:;
            int pos = getBufferPosition();
            char aux = 0;
            // int flag_consume = 0;
            for (int i = 0; i < len; ){
                _hlt();
                aux = getCharAt(pos);
                // if (flag_consume == 1)
                //     consumeBuffAt(pos);
                if ( aux == 0)
                    continue;
                else {
                    buf[i++]=aux;
                    setPos(pos+1);
                }
                // if (aux == '\b'){
                //     if (i>0)
                //         i--;
                // } 
                // if ( aux == '\n'){
                //     flag_consume = 1;
                //     setPos(0);
                // }
                // else {
                //     buf[i++]=aux;
                //     setPos(pos+1);
                // }
                // else 
                //     buf[i++]=aux;
                pos = getBufferPosition();
            }
            // int pos2 = getBufferPosition() - len;
            // for (int i = 0; i < len; i++){
            //     character(GREEN, buf[i]);
            // }
            return;
        default: invalidFd();
    }

}

// static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
// '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 
// 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0, 0 }; //hay que sacarlo de aca

// void sys_read( char *buf, int len, int filedescriptor){
    
//     if (filedescriptor == 0){
//         char aux;
//         int tick, ticks=0;
//         for(int i=0; i < len; ){
//             _hlt();
//             aux=getKey();
//             if(aux>=0 && aux<=256){
//                 if(ScanCodes[aux] == '\b'){
//                     backspace();
//                     if(i>0){
//                         i--;
//                     }
//                 }
//                 else{
//                     buf[i++]=ScanCodes[aux];
//                     // character(WHITE, buf[i-1]);
//                 }
//             }
//             _hlt();_hlt();
//         }
//         character(RED, 'a'); //[DEBUG]
//         return;
//     }
//     invalidFd();
//     return;

// }
