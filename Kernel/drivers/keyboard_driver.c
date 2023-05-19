#include <lib.h>
#include <naiveConsole.h>
#include "include/keyboard_driver.h"
#include "include/videoDriver.h"

static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
'\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 
'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0, 0 };




void keyboard_handler() {
    char key = getKey();
    uint32_t *cursorX = getCursorX();
    uint32_t *cursorY = getCursorY();
    int size = getSize();
    if (key == 0x39) { // Espacio
        drawChar(WHITE, ' ');
        *cursorX += size*8;
        return;
    }
    if (key >= 0 && key <= 256 && ScanCodes[key] != 0) {
        character(ScanCodes[key]);
    }
    return;
}





