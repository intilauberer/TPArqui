#include <stdlib.h>
#include <unistd.h>
#include "include/videoDriver.h"
#include "include/pong.h"
#include "stdin.h"
int player1Score = 0;
int player2Score = 0;

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
    drawRectangle2(color, ball.x, ball.y, ball.size, ball.size);
}

void clearPaddle(Paddle* paddle) {
    drawPaddle(paddle, BLACK);
}

void clearBall(Ball ball) {
    drawBall(ball, BLACK);
}

void movePaddleUp(Paddle* paddle) {
    clearPaddle(paddle);
    if (paddle->y - paddle->speed >= BORDER_SIZE) {
        paddle->y -= paddle->speed;
    } else {
        paddle->y = BORDER_SIZE;
    }
    drawPaddle(paddle, WHITE);
}

void movePaddleDown(Paddle* paddle) {
    clearPaddle(paddle);
    if (paddle->y + paddle->speed + paddle->height <= SCREEN_HEIGHT - BORDER_SIZE) {
        paddle->y += paddle->speed;
    } else {
        paddle->y = SCREEN_HEIGHT - BORDER_SIZE - paddle->height;
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
    if (checkScored(ball, paddle1, paddle2)){
        clearBall(*ball);
        resetGame(ball, paddle1, paddle2, score1, score2);
        return;
    }
    ball->x += ball->speedX;
    ball->y += ball->speedY;


    if ((ball->x <= paddle1->x + paddle1->width && ball->x + ball->size >= paddle1->x && ball->y + ball->size >= paddle1->y && ball->y <= paddle1->y + paddle1->height) ||
        (ball->x + ball->size >= paddle2->x && ball->x <= paddle2->x + paddle2->width && ball->y + ball->size >= paddle2->y && ball->y <= paddle2->y + paddle2->height)) {
        ball->speedX *= -1;
    }

    if (ball->y <= BORDER_SIZE || ball->y + ball->size >= SCREEN_HEIGHT - BORDER_SIZE * 2) {
        ball->speedY *= -1;
    }

    if (ball->x <= BORDER_SIZE) {
        ball->x = BORDER_SIZE + 1;
        ball->speedX = -ball->speedX;

        resetGame(ball, paddle1, paddle2, score1, score2);
    }
    else if (ball->x >= SCREEN_WIDTH - BORDER_SIZE - BALL_SIZE) {
        ball->x = SCREEN_WIDTH - BORDER_SIZE - BALL_SIZE - 1;
        ball->speedX = -ball->speedX;
        resetGame(ball, paddle1, paddle2, score1, score2);
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
    drawWordColorAt(hexColor, "Press any other key to continue.", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+126);
}

void pauseGame(){
    pauseModular(WHITE);
}
void unpause(){
    pauseModular(BLACK);
}

// void checkScored(Ball* ball){
//     if (ball->x < ball->speedX)
//         player2Score++;
//     if (ball->x > ball->speedX - SCREEN_WIDTH )
//         player1Score++;
// }       

void Pong() {
    Paddle paddle1 = {50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, UP};
    Paddle paddle2 = {SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, DOWN};
    Ball ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SPEED, BALL_SPEED};

    player1Score = 0;
    player2Score = 0;

    clear(BLACK);
    setFontSize(24);
    drawWordColorAt(WHITE, "PONG", SCREEN_WIDTH/2-270, SCREEN_HEIGHT/2-200);
    setFontSize(DEFAULT_FONT_SIZE);
    drawWordColorAt(WHITE, "Press any key to begin: ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+100);
    char c = sys_read(&c, 1, 0);
    char p = 0;
    clear(BLACK);
    drawBorders();
    drawMiddleLine();  
    drawPaddle(&paddle1, WHITE);  
    drawPaddle(&paddle2, WHITE);
    showScoreCard(WHITE);

    while (1) {
        showScoreCard(WHITE);
        c = getCharAt(getBufferPosition()-1);
        if (c=='P'){
            pauseGame();
            sys_read(&p, 1, 0);
            if (p == 'X'){
                clear();
                return;
            } 
            unpause();
        }
        if (paddle1.direction == UP){
            movePaddleUp(&paddle1);
            if (c == 'S')
                paddle1.direction = DOWN;
        }
        else{
            movePaddleDown(&paddle1);
            if (c == 'W')
                paddle1.direction = UP;
        }

        if (paddle2.direction == UP){
            movePaddleUp(&paddle2);
            if (c == 'K')
                paddle2.direction = DOWN;
        }
        else{
            movePaddleDown(&paddle2);
            if (c == 'I')
                paddle2.direction = UP;
        }

        moveBall(&ball, &paddle1, &paddle2, &player1Score, &player2Score);
        // if (ball.y + ball.size < paddle1.y + paddle1.height / 2) {
        //     movePaddleUp(&paddle1);
        // }
        // else if (ball.y > paddle1.y + paddle1.height / 2) {
        //     movePaddleDown(&paddle1);
        // }
        // if (ball.y + ball.size < paddle2.y + paddle2.height / 2) {
        //     movePaddleUp(&paddle2);
        // }

        // else if (ball.y > paddle2.y + paddle2.height / 2) {
        //     movePaddleDown(&paddle2);
        // }

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

        sleepms(1);
    }
}
