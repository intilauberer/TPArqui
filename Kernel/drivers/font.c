#include "include/font.h"
#include <stdint.h>

uint8_t * getBitmap(char character){
    return *(__font__+character-15);
}