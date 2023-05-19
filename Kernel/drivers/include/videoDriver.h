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
void putPixel(uint32_t hexColor, uint32_t x, uint32_t y);
void paintScreen(uint32_t hexColor);
void fillSection(uint32_t hexColor, int startY, int endY);
// void drawChar(uint32_t hexColor,
//  			  uint32_t backHexColor,
// 			  uint8_t strokeSize,
// 			  uint32_t x, 
// 			  uint32_t y, 
// 			  char character);
void boke();
void drawRectangle(uint32_t hexColor, uint32_t b, uint32_t h, uint32_t x, uint32_t y);


void drawCircle(uint32_t hexColor, uint32_t b, uint32_t radius, uint32_t x, uint32_t y);

void drawSquare(uint32_t hexColor, uint32_t side_length, uint32_t x, uint32_t y);

// char ellipseFormula(uint32_t height, uint32_t width, uint32_t x_center, uint32_t y_center, uint32_t x, uint32_t y);

// void drawEllipse(uint32_t hexColor, uint32_t height, uint32_t width, uint32_t x, uint32_t y);
void drawChar(uint32_t hexColor, char character);

uint32_t *getCursorX();
  
uint32_t *getCursorY();