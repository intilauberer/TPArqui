#include <lib.h>
#include <naiveConsole.h>
#include "include/keyboard_driver.h"
#include "include/videoDriver.h"
#include "../stdin.h"
#include "defs.h"
#include "interrupts.h"
#include "registers.h"





void keyboard_handler() {
    uint16_t key = getKey();
    if (key == NULL)
        return key;
    //_hlt();
    uint32_t *cursorX = getCursorX();
    uint32_t *cursorY = getCursorY();
    int size = getSize();
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

    // if (key == 0x39) { // Espacio
    //     buff[buff_pos] = ' ';
    //     setPos(buff_pos+1);
    //     return key;
    // }

    // if (key >= 0 && key <= 256 && ScanCodes[key] != 0) {
        // if (buff_pos+1 < BUFF_SIZE){
        //     setPos(buff_pos+1);
        //     buff[buff_pos+1] = 0;
        // } else {
        //     setPos(0);   
        //     buff[0] = 0;
        // }
    //     buff[buff_pos] = ScanCodes[key];
    // }
    return;
}





