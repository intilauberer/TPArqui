
#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>


void keyboard_handler();
extern int getKey();
void newline(uint32_t *cursorX, uint32_t *cursorY);
void backspace(uint32_t *cursorX, uint32_t *cursorY);
#endif /* KEYBOARD_DRIVER_H */