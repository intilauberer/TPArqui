#include <lib.h>
#include <naiveConsole.h>
#include "include/keyboard_driver.h"
#include "include/videoDriver.h"
#include "../keyboard_buffer.h"
#include "defs.h"
#include "interrupts.h"
#include "registers.h"
#include "include/ScanCodes.h"



void keyboard_handler() {
    uint16_t key = getKey();
    if (key == NULL)
        return;
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
    
    if (ScanCodes[key] == ';'){
        saveState();
        flag_snapshot_taken = 1;
    }
    return;
}






