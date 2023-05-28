#include <stdlib.h>
#include <unistd.h>
#include "include/videoDriver.h"
#include "include/pong.h"
#include "stdin.h"
#include "drivers/include/keyboard_driver.h"
#include "time.h"

unsigned int BORDER_SIZE = 10;

unsigned int PADDLE_WIDTH = 10;
unsigned int PADDLE_HEIGHT = 100;
unsigned int PADDLE_SPEED = 10;

unsigned int BALL_SIZE = 10;
unsigned int BALL_SPEED = 10;

unsigned int BALL_COLOR = WHITE;
unsigned int PADDLE_COLOR = WHITE;
unsigned int BACKGROUND_COLOR = BLACK;

uint64_t player1Up;
uint64_t player1Upbeak;
uint64_t player1Down;
uint64_t player1Downbeak;
uint64_t player2Up;
uint64_t player2Upbeak;
uint64_t player2Down;
uint64_t player2Downbeak;

int player1Score = 0;
int player2Score = 0;
int movement_vector[] = {-1,1,0};


void setPlayer1Up(uint64_t key) {
    player1Up = key;
    player1Upbeak = key + 0x80;
}

void setPlayer1Down(uint64_t key) {
    player1Down = key;
    player1Downbeak = key + 0x80;
}


void setPlayer2Up(uint64_t key) {
    player2Up = key;
    player2Upbeak = key + 0x80;
}

void setPlayer2Down(uint64_t key) {
    player2Down = key;
    player2Downbeak = key + 0x80;
}


void drawRectangle2(uint64_t color, int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            putPixel(color, x + j, y + i);
        }
    }
}

void drawPaddle(Paddle* paddle, uint64_t color) {
    drawRectangle2(color, paddle->x, paddle->y, paddle->width, paddle->height);
}

void drawBall(Ball ball, uint64_t color) {
    int radius = ball.size / 2;
    int centerX = ball.x + radius;
    int centerY = ball.y + radius;
    int squaredRadius = radius * radius;

    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if ((x * x) + (y * y) <= squaredRadius) {
                putPixel(color, centerX + x, centerY + y);
            }
        }
    }
}
void clearPaddle(Paddle* paddle) {
    drawPaddle(paddle, BLACK);
}

void clearBall(Ball ball) {
    drawBall(ball, BLACK);
}

void movePaddle(Paddle* paddle) {
    clearPaddle(paddle);
    int move;
    
    if (paddle->direction == UP) {
        move = paddle->y - movement_vector[paddle->direction] * paddle->speed;
        if (move >= BORDER_SIZE) {
            paddle->y = move;
        } else {
            paddle->y = BORDER_SIZE;
            paddle->direction = STOP;
        }
    } else if (paddle->direction == DOWN) {
        move = paddle->y + paddle->speed;
        if (move + paddle->height <= SCREEN_HEIGHT - BORDER_SIZE) {
            paddle->y = move;
        } else {
            paddle->y = SCREEN_HEIGHT - BORDER_SIZE - paddle->height;
            paddle->direction = STOP;
        }
    }
    
    drawPaddle(paddle, WHITE);
}




void showScoreCard(uint64_t hexColor){
    setFontSize(SCORE_CARD_FONT_SIZE);
    characterAt(hexColor, player1Score+'0', SCORE_CARD_X-30, SCORE_CARD_Y+50);
    characterAt(hexColor, player2Score+'0', SCORE_CARD_X+30, SCORE_CARD_Y+50);
}
void updateScore(int player){
    if (player == 1){
        characterAt(BLACK, player1Score+'0', SCORE_CARD_X-30, SCORE_CARD_Y+50);
        player1Score++;
        characterAt(WHITE, player1Score+'0', SCORE_CARD_X-30, SCORE_CARD_Y+50);
    } else {
        characterAt(BLACK, player2Score+'0', SCORE_CARD_X+30, SCORE_CARD_Y+50);
        player2Score++;
        characterAt(WHITE, player2Score+'0', SCORE_CARD_X+30, SCORE_CARD_Y+50);
    }
}
void clearScoreCard(){
    showScoreCard(BLACK);
}

char checkScored(Ball* ball, Paddle* paddle1, Paddle* paddle2){
    if (ball->x + ball->size < paddle1->x + paddle1->width){
        updateScore(2);
        return 1;
    }
    if (ball->x - ball->size > paddle2->x){
        updateScore(1);
        return 1;
    }
    return 0;
}       

void moveBall(Ball* ball, Paddle* paddle1, Paddle* paddle2, int* score1, int* score2) {
    clearBall(*ball);
    
    if (checkScored(ball, paddle1, paddle2)) {
        clearBall(*ball);
        resetGame(ball, paddle1, paddle2, score1, score2);
        return;
    }
    
    ball->x += ball->speedX;
    ball->y += ball->speedY;

    if (ball->x <= BORDER_SIZE) {
        ball->x = BORDER_SIZE;
        ball->speedX = -ball->speedX;
    } else if (ball->x + ball->size >= SCREEN_WIDTH - BORDER_SIZE) {
        ball->x = SCREEN_WIDTH - BORDER_SIZE - ball->size;
        ball->speedX = -ball->speedX;
    }

    if (ball->y <= BORDER_SIZE) {
        ball->y = BORDER_SIZE;
        ball->speedY = -ball->speedY;
    } else if (ball->y + ball->size >= SCREEN_HEIGHT - BORDER_SIZE * 2) {
        ball->y = SCREEN_HEIGHT - BORDER_SIZE * 2 - ball->size;
        ball->speedY = -ball->speedY;
    }

    if ((ball->x <= paddle1->x + paddle1->width && ball->x + ball->size >= paddle1->x && ball->y + ball->size >= paddle1->y && ball->y <= paddle1->y + paddle1->height) ||
        (ball->x + ball->size >= paddle2->x && ball->x <= paddle2->x + paddle2->width && ball->y + ball->size >= paddle2->y && ball->y <= paddle2->y + paddle2->height)) {
        ball->speedX *= -1;
    }

    drawBall(*ball, WHITE);
}



void resetGame(Ball* ball, Paddle* paddle1, Paddle* paddle2, int* score1, int* score2) {
    clearPaddle(paddle1);
    clearPaddle(paddle2);

    ball->x = SCREEN_WIDTH / 2 - ball->size / 2; 
    ball->y = SCREEN_HEIGHT / 2 - ball->size / 2;

    ball->speedX *= -1;

    paddle1->y = SCREEN_HEIGHT / 2 - paddle1->height / 2;
    paddle2->y = SCREEN_HEIGHT / 2 - paddle2->height / 2;

    drawPaddle(paddle1, WHITE);
    drawPaddle(paddle2, WHITE);
}

void drawMiddleLine(){
    for (int i = 0; i < SCREEN_HEIGHT; i+= 20){
        drawRectangle2(WHITE, SCREEN_WIDTH/2-5, i, 10, 10);
    }
}



void drawBorders() {
    drawRectangle2(WHITE, 0, 0, SCREEN_WIDTH, BORDER_SIZE); 
    drawRectangle2(WHITE, 0, SCREEN_HEIGHT - BORDER_SIZE, SCREEN_WIDTH, BORDER_SIZE);  
}
void pauseModular(uint64_t hexColor){
    setFontSize(18);
    drawWordColorAt(hexColor, "PAUSED", SCREEN_WIDTH/2-270, SCREEN_HEIGHT/2-200);
    setFontSize(DEFAULT_FONT_SIZE);
    drawWordColorAt(hexColor, "Press X to exit. ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+100);
    drawWordColorAt(hexColor, "Press C to acces configuration. ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+130);
    drawWordColorAt(hexColor, "Press any other key to continue.", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+160);
}

void pauseGame(){
    pauseModular(WHITE);
}
void unpause(){
    pauseModular(BLACK);
}

void training(Ball* ball, Paddle* paddle2) {
    if (ball->y + ball->size < paddle2->y + paddle2->height / 2) {
        paddle2->direction = UP;
    } else if (ball->y > paddle2->y + paddle2->height / 2) {
        paddle2->direction = DOWN;
    } else {
        paddle2->direction = STOP;
    }

    movePaddle(paddle2);
}

int benchmark(){
    int ticks = ticks_elapsed();
    for (long i = 0; i < 1000000000; i++);
    int ticks2 = ticks_elapsed();
    return ticks2-ticks;
}

void sleepbm(int bm){
    for (long i = 0; i < 50000000;i+=bm);
}
void options() {
    drawWordColorAt(WHITE, "CONFIGURATION", SCREEN_WIDTH/2-270, 0);
    drawWordColorAt(WHITE, "Press 1 to change the ball speed", 0, 30);
    drawWordColorAt(WHITE, "Press 2 to change the paddle speed", 0, 60);
    drawWordColorAt(WHITE, "Press 3 to change the experimental refresh rate", 0, 90);
    drawWordColorAt(WHITE, "Press 4 to change the ball size", 0, 120);
    drawWordColorAt(WHITE, "Press 5 to change the paddle size", 0, 150);
    drawWordColorAt(WHITE, "Press 6 to change the paddle height", 0, 180);
    drawWordColorAt(WHITE, "Press 7 to change the paddle width", 0, 210);
    drawWordColorAt(WHITE, "Press 8 to change the ball color", 0, 240);
    drawWordColorAt(WHITE, "Press 9 to change the paddle color", 0, 270);
    drawWordColorAt(WHITE, "Press 0 to change the background color", 0, 300);
    drawWordColorAt(WHITE, "Press X to exit", 0, 330);
}


int getNumber(){
    char c;
    int number = 0;
    sys_read(&c, 1, 0);
    int i = 0;
    while (c != '\n') {
        sys_read(&c, 1, 0);
        if (c >= '0' && c <= '9') {
            number = number * 10 + (c - '0');
            characterAt(WHITE, c, SCREEN_WIDTH/2 + i, SCREEN_HEIGHT/2); 
            i+=16;
        }
    }
    return number;
}

void configuration(){
    char c;
    options();
   while (1) {
        options();
        sys_read(&c, 1, 0);
        switch (c) {
            case '1': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current ball speed: ", 0, SCREEN_HEIGHT/2);
               // drawNumberColor(WHITE, BALL_SPEED, 200, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new ball speed: ", 0, SCREEN_HEIGHT/2+50);
                int speed = getNumber();
                drawNumberColor( speed, WHITE);
                if (speed > 0) {
                    BALL_SPEED = speed;
                }
                break;
            }
            case '2': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current paddle speed: ", 0, SCREEN_HEIGHT/2);
                //drawNumberColor(WHITE, PADDLE_SPEED, 200, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new paddle speed: ", 0, SCREEN_HEIGHT/2+50);
                int speed = getNumber();
                if (speed > 0) {
                    PADDLE_SPEED = speed;
                }
                break;
            }
            case '3': {

                break;
            }
            case '4': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current ball size: ", 0, SCREEN_HEIGHT/2);
               // drawNumberColor(WHITE, BALL_SIZE, 150, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new ball size: ", 0, SCREEN_HEIGHT/2+50);
                int size = getNumber();
                if (size > 0) {
                    BALL_SIZE = size;
                }
                break;
            }
            case '5': {
                
            }
            case '6': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current paddle height: ", 0, SCREEN_HEIGHT/2);
               // drawNumberColor(WHITE, PADDLE_HEIGHT, 220, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new paddle height: ", 0, SCREEN_HEIGHT/2+50);
                int height = getNumber();
                if (height > 0) {
                    PADDLE_HEIGHT = height;
                }
                break;
            }
            case '7': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current paddle width: ", 0, SCREEN_HEIGHT/2);
               // drawNumberColor(WHITE, PADDLE_WIDTH, 220, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new paddle width: ", 0, SCREEN_HEIGHT/2+50);
                int width = getNumber();
                if (width > 0) {
                    PADDLE_WIDTH = width;
                }
                break;
            }
            case '8': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current ball color: ", 0, SCREEN_HEIGHT/2);
                //drawNumberColor(WHITE, BALL_COLOR, 180, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new ball color (1-15): ", 0, SCREEN_HEIGHT/2+50);
                int color = getNumber(); //cambiar a getColor
                if (color >= 1 && color <= 15) {
                    BALL_COLOR = color;
                }
                break;
            }
            case '9': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current paddle color: ", 0, SCREEN_HEIGHT/2);
                //drawNumberColor(WHITE, PADDLE_COLOR, 200, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new paddle color (1-15): ", 0, SCREEN_HEIGHT/2+50);
                int color = getNumber();
                if (color >= 1 && color <= 15) {
                    PADDLE_COLOR = color;
                }
                break;
            }
            case '0': {
                clear(BLACK);
                drawWordColorAt(WHITE, "Current background color: ", 0, SCREEN_HEIGHT/2);
                //drawNumberColor(WHITE, BACKGROUND_COLOR, 220, SCREEN_HEIGHT/2);
                drawWordColorAt(WHITE, "Enter the new background color (1-15): ", 0, SCREEN_HEIGHT/2+50);
                int color = getNumber();
                if (color >= 1 && color <= 15) {
                    BACKGROUND_COLOR = color;
                }
                break;
            }
            case 'X': {
                clear(BLACK);
                return;
            }
            default: {
                break;
            }
        }
   }
}

// Paddle paddle1;
// Paddle paddle2;
// Ball ball;

// setPaddle(Paddle *paddle, int x, int y, int width, int height, int speed) {
//     paddle->x = x;
//     paddle->y = y;
//     paddle->width = width;
//     paddle->height = height;
//     paddle->speed = speed;

// }

void Pong() {
   
    int experimental = 0;
    int setting = 0;
    setFontSize(24);
    drawWordColorAt(WHITE, "PONG", SCREEN_WIDTH/2-270, SCREEN_HEIGHT/2-200);
    setFontSize(DEFAULT_FONT_SIZE);
    drawWordColorAt(WHITE, "Press E to enable experimental refresh rate", 0, SCREEN_HEIGHT/2+100);
    drawWordColorAt(WHITE, "Press any other key for default refresh rate", 0, SCREEN_HEIGHT/2+130);
    char e;
    sys_read(&e, 1, 0);
    drawWordColorAt(BLACK, "Press E to enable experimental refresh rate", 0, SCREEN_HEIGHT/2+100);
    drawWordColorAt(BLACK, "Press any other key for default refresh rate", 0, SCREEN_HEIGHT/2+130);
    if ( e == 'E'){
        drawWordColorAt(WHITE, "Wait until benchmark is complete...", 0, SCREEN_HEIGHT/2+100);
        experimental = 1;
        setting = benchmark();
        drawWordColorAt(BLACK, "Wait until benchmark is complete...", 0, SCREEN_HEIGHT/2+100);
    }
    drawWordColorAt(WHITE, "Press T for training", 0, SCREEN_HEIGHT/2+100);
     drawWordColorAt(WHITE, "Press C for configuration", 0, SCREEN_HEIGHT/2+130);
    drawWordColorAt(WHITE, "Press any other key to begin 2 player PONG: ",0, SCREEN_HEIGHT/2+160);
    drawWordColorAt(WHITE, "Player 1 goes up with \"W\" and down with \"S\"",0, SCREEN_HEIGHT/2+190);
    drawWordColorAt(WHITE, "Player 2 goes up with \"I\" and down with \"K\"",0, SCREEN_HEIGHT/2+220);
    int Training = 0;
    char t;
    sys_read(&t, 1, 0);
    if( t == 'C'){
        clear(BLACK);
        configuration();
    }
    if ( t == 'T'){
        Training = 1;
    }
    uint16_t c;
    char p = 0;
    Paddle paddle1 = {50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, STOP};
    Paddle paddle2 = {SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, STOP};
    Ball ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SPEED, BALL_SPEED};
    clear(BLACK);
    drawBorders();
    drawMiddleLine();  
    drawPaddle(&paddle1, WHITE);  
    drawPaddle(&paddle2, WHITE);
    showScoreCard(WHITE);
    int pos = getBufferPosition();
    long k =0;
   
    
    while (1) {
        showScoreCard(WHITE);
        if (c==0x19){
            pauseGame();
            sys_read(&p, 1, 0);
            if (p == 'X'){
                clear();
                return;
            }
            if (p == 'C'){
                clear(BLACK);
                configuration();
            };
            unpause();
        }
        while (pos <= getBufferPosition()) {
            c = getCharAt(pos++-1);
            if (c == 0x14) {
            Training = 1;
            }
            if (c == 0x11){
                paddle1.direction = UP;
            }
            else if (c == 0x91){
                if (paddle1.direction == UP)
                    paddle1.direction = STOP; 
            }  

            else if (c == 0x1F) 
                paddle1.direction = DOWN;

            else if (c == 0x9F){
                if (paddle1.direction == DOWN)
                    paddle1.direction = STOP;
            }
            if (!Training){
                 if (c == 0x17){
                    paddle2.direction = UP;
                }
                else if (c == 0x97){
                    if (paddle2.direction == UP)
                        paddle2.direction = STOP; 
                }   

                else if (c == 0x25)
                    paddle2.direction = DOWN;

                else if (c == 0xA5){
                    if (paddle2.direction == DOWN)
                        paddle2.direction = STOP;
                }
            }
            }
            if (Training){
                training(&ball, &paddle2);
            }
            movePaddle(&paddle1);
            movePaddle(&paddle2);
            moveBall(&ball, &paddle1, &paddle2, &player1Score, &player2Score);

            if (player1Score >= 3 || player2Score >= 3) {
                clearColor(BLACK);
                setFontSize(18);
                setFontSize(DEFAULT_FONT_SIZE);
                drawWordColorAt(WHITE, "GAME OVER", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-170);
                if(player1Score>player2Score){
                    drawWordColorAt(WHITE, "PLAYER 1 WINS", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-130);
                }
                else{
                    drawWordColorAt(WHITE, "PLAYER 2 WINS", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-130);
                }
                drawWordColorAt(WHITE, "Press X to exit. ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-100);
                drawWordColorAt(WHITE, "Press any other key to play again.", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-75);
                sys_read(&p, 1, 0);
                if (p == 'X'){
                    clear();
                    return;
                }
                clear();
                player1Score = 0;
                player2Score = 0;
                resetGame(&ball, &paddle1, &paddle2, &player1Score, &player2Score);
                drawMiddleLine();
            }
            drawMiddleLine();
            sleepms(1);
            if (experimental)
                sleepbm(setting);
            else sleepms(1);
    }
}