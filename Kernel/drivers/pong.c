#include <stdlib.h>
#include <unistd.h>
#include "include/videoDriver.h"
#include "include/pong.h"

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

void moveBall(Ball* ball, Paddle* paddle1, Paddle* paddle2, int* score1, int* score2) {
    clearBall(*ball);
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




void drawBorders() {
    drawRectangle2(WHITE, 0, 0, SCREEN_WIDTH, BORDER_SIZE); 
    drawRectangle2(WHITE, 0, SCREEN_HEIGHT - BORDER_SIZE, SCREEN_WIDTH, BORDER_SIZE);  
}

void Pong() {
    Paddle paddle1 = {50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED};
    Paddle paddle2 = {SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED};
    Ball ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SPEED, BALL_SPEED};

    player1Score = 0;
    player2Score = 0;

    paintScreen(BLACK);
    drawBorders();  
    drawPaddle(&paddle1, WHITE);  
    drawPaddle(&paddle2, WHITE);


    char c;
    while (1) {
        // c = getc();
        // sys_read(&c, 1, 0);
        // if (c == 'w')
        //     movePaddleUp(&paddle1);
        // else if (c == 's')
        //     movePaddleDown(&paddle1);
        // else if (c == 'i')
        //     movePaddleUp(&paddle2);
        // else if (c == 'k')
        //     movePaddleDown(&paddle2);

        moveBall(&ball, &paddle1, &paddle2, &player1Score, &player2Score);
        if (ball.y + ball.size < paddle1.y + paddle1.height / 2) {
            movePaddleUp(&paddle1);
        }
        else if (ball.y > paddle1.y + paddle1.height / 2) {
            movePaddleDown(&paddle1);
        }
        if (ball.y + ball.size < paddle2.y + paddle2.height / 2) {
            movePaddleUp(&paddle2);
        }

        else if (ball.y > paddle2.y + paddle2.height / 2) {
            movePaddleDown(&paddle2);
        }

        if (player1Score >= 10 || player2Score >= 10) {
            resetGame(&ball, &paddle1, &paddle2, &player1Score, &player2Score);
        }

        sleepms(1);
    }
}
