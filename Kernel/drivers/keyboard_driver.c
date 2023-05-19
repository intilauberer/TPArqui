#include <lib.h>
#include <naiveConsole.h>
#include "include/keyboard_driver.h"
#include "include/videoDriver.h"

static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
'\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 
'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 0, 0 };




void backspace(uint32_t *cursorX, uint32_t *cursorY){
     if (*cursorX > 0) {
            *cursorX -= 8;
        } else if (*cursorY > 0 && *cursorX == 0) { // El cursor está al principio de una línea
            // Borra el último carácter de la línea anterior
            *cursorY -= 16;
            *cursorX = getMaxWidth() - 8; // Establece el cursorX al último carácter de la línea anterior
            
        }
		int height = getMaxHeight();
		if (*cursorY >= height / 3 && *cursorY < (height / 3) * 2) { // Estamos en el segundo tercio de la pantalla
                drawRectangle(YELLOW, *cursorX, *cursorY, 8, 16); // Dibuja un rectángulo amarillo en lugar del carácter borrado
            } else {
                drawRectangle(BLUE, *cursorX, *cursorY, 8, 16); // Dibuja un rectángulo azul en lugar del carácter borrado
            }
        return;
}

void newline(uint32_t *cursorX, uint32_t *cursorY){
    *cursorX = 0;
    *cursorY += 16;
    return;
}



void keyboard_handler() {
    char key = getKey();
    uint32_t *cursorX = getCursorX();
    uint32_t *cursorY = getCursorY();

    int size = 1;
    if (key == 0x39) { // Espacio
        drawChar(WHITE, ' ');
        *cursorX += 8;
        return;
    }
    if (ScanCodes[key] == '\b') { // Retroceso
       backspace(cursorX, cursorY);
        return;
    }
    if (ScanCodes[key] == '\t') { // Tabulación
        int tabWidth = 32;
        int spaces = tabWidth - (*cursorX / 8) % tabWidth;

        for (int i = 0; i < spaces; i++) {
            drawChar(WHITE, ' ');
            *cursorX += 8;
        }
        return;
    }
    if (ScanCodes[key] == '\n') { // Salto de línea
        newline(cursorX, cursorY);
        return;
    }
    if (key >= 0 && key <= 256 && ScanCodes[key] != 0) { // Carácter
        if (*cursorX >= getMaxWidth()) {
            *cursorX = 0;
            *cursorY += 16;
        }
        drawChar(WHITE, ScanCodes[key]);
        *cursorX += 8;
        return;
    }
}





