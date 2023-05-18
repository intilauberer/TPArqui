#include "include/videoDriver.h"

unsigned int SCREEN_WIDTH = 1024;
unsigned int SCREEN_HEIGHT = 768;
unsigned int BPP = 3;

struct vbe_mode_info_structure { 
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00; 


void putPixel(uint32_t hexColor, uint32_t x, uint32_t y) {
	uint8_t * screen = (uint8_t *) ((uint64_t) (VBE_mode_info->framebuffer));
    uint32_t offset = VBE_mode_info->pitch*y + x*3;
    
    screen[offset] = TO_RED(hexColor);
    screen[offset+1] = TO_BLUE(hexColor);
    screen[offset+2] = TO_GREEN(hexColor);
}

void drawRectangle(uint32_t hexColor, uint32_t b, uint32_t h, uint32_t x, uint32_t y){
	for (uint32_t x_aux = x; x_aux < x+b; x_aux++){
		for (uint32_t y_aux = y; y_aux < y+h; y_aux++){
			putPixel(hexColor,x_aux,y_aux);
		}
	}
}



// char ellipseFormula(uint32_t height, uint32_t width, uint32_t x_center, uint32_t y_center, uint32_t x, uint32_t y) {
//     double x_normalized = (double)(x - x_center) / width;
//     double y_normalized = (double)(y - y_center) / height;
    
//     double result = (x_normalized * x_normalized) + (y_normalized * y_normalized);
    
//     if (result <= 1.0) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

// void drawEllipse(uint32_t hexColor, uint32_t height, uint32_t width, uint32_t x, uint32_t y) {
//     uint32_t top_left_x = x;
//     uint32_t top_left_y = y;
//     uint32_t bottom_right_x = x + width;
//     uint32_t bottom_right_y = y + height;
    
//     for (uint32_t curr_x = top_left_x; curr_x <= bottom_right_x; curr_x++) {
//         for (uint32_t curr_y = top_left_y; curr_y <= bottom_right_y; curr_y++) {
//             if (ellipseFormula(height, width, x + (width / 2), y + (height / 2), curr_x, curr_y)) {
//                 putPixel(hexColor, curr_x, curr_y);
//             }
//         }
//     }
// }


void drawCircle(uint32_t hexColor, uint32_t b, uint32_t radius, uint32_t x, uint32_t y);

void drawSquare(uint32_t hexColor, uint32_t side_length, uint32_t x, uint32_t y){
	drawRectangle(hexColor, side_length, side_length, x, y);
}

void fillSection(uint32_t hexColor, int startY, int endY) {
    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < VBE_mode_info->width; x++) {
            putPixel(hexColor, x, y);
        }
    }
}

void boke() {
    int height = VBE_mode_info->height / 3 ;

    fillSection(BLUE, 0, height);


    fillSection(YELLOW, height, height * 2);

 
    fillSection(BLUE, height * 2, VBE_mode_info->height);
}



void paintScreen(uint32_t hexColor){
	for (int x = 0; x < VBE_mode_info->width; x++){
		for (int y = 0; y < VBE_mode_info-> pitch; y++){
			putPixel(hexColor,x,y);
		}
	}
	return;
}

void drawChar(uint32_t hexColor,
 			  uint32_t backHexColor,
			  uint8_t strokeSize,
			  uint32_t x, 
			  uint32_t y, 
			  char character){
	uint32_t x_aux = x;
	uint32_t y_aux = y;
		
	return;

}