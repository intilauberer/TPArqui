
#include "videoDriver.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 800
#define BORDER_SIZE 10

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100
#define PADDLE_SPEED 13

#define BALL_SIZE 10
#define BALL_SPEED 10

#define SCORE_X (SCREEN_WIDTH / 2 - 10)
#define SCORE_Y (BORDER_SIZE + 10)
#define SCORE_WIDTH 20
#define SCORE_HEIGHT 20

#define CHARACTER_WIDTH 5
#define CHARACTER_HEIGHT 8
#define SCORE_PADDING 10
#define UP 1
#define DOWN 0

#define SCORE_CARD_X (SCREEN_WIDTH + 10)
#define SCORE_CARD_Y (SCREEN_HEIGHT - 568)
#define SCORE_CARD_FONT_SIZE 2

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int speed;
    char direction;
} Paddle;

typedef struct {
    int x;
    int y;
    int size;
    int speedX;
    int speedY;
} Ball;

void drawPaddle(Paddle* paddle, uint64_t color);
void clearPaddle(Paddle* paddle);
void movePaddleUp(Paddle* paddle);
void movePaddleDown(Paddle* paddle);
void moveBall(Ball* ball, Paddle* paddle1, Paddle* paddle2, int* score1, int* score2);
void drawBorders();
void Pong();

