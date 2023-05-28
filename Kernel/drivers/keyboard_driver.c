#include <lib.h>
#include <naiveConsole.h>
#include "include/keyboard_driver.h"
#include "include/videoDriver.h"
#include "../stdin.h"
#include "defs.h"
#include "interrupts.h"
#include "registers.h"




// static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
// '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 
// 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0, 0 }; //hay que sacarlo de aca

void keyboard_handler() {
    uint16_t key = getKey();
    if (key == NULL)
        return key;
    uint16_t * buff = getBufferAddress();
    int buff_pos = getBufferPosition();
    
     if (buff_pos+1 < BUFF_SIZE){
            setPos(buff_pos+1);
            buff[buff_pos+1] = 0;
        } else {
            setPos(0);   
            buff[0] = 0;
        }
    buff[buff_pos] = key;
    
    if (key[ScanCodes] == ';'){
        saveState();
        flag_snapshot_taken = 1;
    }
    return;
}





