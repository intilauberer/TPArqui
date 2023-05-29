
#include "videoDriver.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 800



#define SCORE_X (SCREEN_WIDTH / 2 - 10)
#define SCORE_Y (BORDER_SIZE + 10)
#define SCORE_WIDTH 20
#define SCORE_HEIGHT 20

#define CHARACTER_WIDTH 5
#define CHARACTER_HEIGHT 8
#define SCORE_PADDING 10
#define UP 1
#define DOWN 0
#define STOP 2

#define SCORE_CARD_X 385
#define SCORE_CARD_Y 10
#define SCORE_CARD_FONT_SIZE 4


typedef struct {
    int x;
    int y;
    int width;
    int height;
    int speed;
    char direction;
    uint64_t color;
} Paddle;

typedef struct {
    int x;
    int y;
    int size;
    int speedX;
    int speedY;
    uint64_t color;
} Ball;

void drawPaddle(Paddle* paddle, uint64_t color);
void clearPaddle(Paddle* paddle);
void movePaddleUp(Paddle* paddle);
void movePaddleDown(Paddle* paddle);
void moveBall();
void drawBorders();
void Pong();
void drawMiddleLine();
