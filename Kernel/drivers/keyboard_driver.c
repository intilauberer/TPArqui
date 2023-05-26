#include <lib.h>
#include <naiveConsole.h>
#include "include/keyboard_driver.h"
#include "include/videoDriver.h"
#include "../stdin.h"
#include "defs.h"
#include "interrupts.h"
#include "registers.h"

static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
'\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 
'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0, 0 };




char keyboard_handler() {
    char key = getKey();
    if (key == NULL)
        return key;
    //_hlt();
    uint32_t *cursorX = getCursorX();
    uint32_t *cursorY = getCursorY();
    int size = getSize();
    char * buff = getBufferAddress();
    int buff_pos = getBufferPosition();

    if (key[ScanCodes] == ';'){
        saveState();
        flag_snapshot_taken = 1;
    }

    if (key == 0x39) { // Espacio
        buff[buff_pos] = ' ';
        setPos(buff_pos+1);
        return key;
    }

    if (key >= 0 && key <= 256 && ScanCodes[key] != 0) {
        if (buff_pos+1 < BUFF_SIZE){
            setPos(buff_pos+1);
            buff[buff_pos+1] = 0;
        } else {
            setPos(0);   
            buff[0] = 0;
        }
        buff[buff_pos] = ScanCodes[key];
    }
    return ScanCodes[key];
}





