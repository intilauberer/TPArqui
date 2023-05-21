#include <stdint.h>

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define YELLOW 0xFFFF00
#define ORANGE 0xFFA500

#define TO_RED(hex) hex & 0xFF
#define TO_BLUE(hex) (hex >> 8) & 0xFF
#define TO_GREEN(hex) (hex >> 16) & 0xFF
#define isMinusc(x) ((x)<='a'?(((x)>='z')?1:0):0)
void putPixel(uint64_t hexColor, uint32_t x, uint32_t y);
void paintScreen(uint64_t hexColor);
void fillSection(uint64_t hexColor, int startY, int endY);
void boke();
void drawRectangle(uint64_t hexColor, uint32_t b, uint32_t h, uint32_t x, uint32_t y);


void drawCircle(uint64_t hexColor, uint32_t b, uint32_t radius, uint32_t x, uint32_t y);

void put_square(uint32_t x, uint32_t y, uint32_t size, uint64_t hexColor);
void drawChar(uint64_t hexColor, char character);
void changeSize(uint32_t new_size);
uint32_t *getCursorX();
  
uint32_t *getCursorY();

unsigned int getMaxWidth();

unsigned int getMaxHeight();

void newline();
void backspace();
void tab();
void character(uint64_t hexColor, char c);

void drawWordColor(uint64_t hexColor, char* word);
void drawWord(char* word);
void invalidFd();