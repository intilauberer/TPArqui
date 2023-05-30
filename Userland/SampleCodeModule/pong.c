#include <stdlib.h>
#include <unistd.h>
#include "include/pong.h"
#include "include/UserSyscalls.h"
#include "include/utils.h"

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define YELLOW 0xFFFF00
#define ORANGE 0xFFA500
#define DEFAULT_FONT_SIZE 16

// unsigned int BORDER_SIZE = 10;

// unsigned int PADDLE_WIDTH = 10;
// unsigned int PADDLE_HEIGHT = 100;
// unsigned int PADDLE_SPEED = 4;

// unsigned int BALL_SIZE = 10;
// unsigned int BALL_SPEED = 3;

// uint64_t BALL_COLOR = WHITE;
// uint64_t PADDLE_COLOR = WHITE;
// uint64_t BACKGROUND_COLOR = BLACK;

// uint64_t player1Up;
// uint64_t player1Upbeak;
// uint64_t player1Down;
// uint64_t player1Downbeak;
// uint64_t player2Up;
// uint64_t player2Upbeak;
// uint64_t player2Down;
// uint64_t player2Downbeak;

// Paddle paddle1;
// Paddle paddle2;
// Ball ball;

// int player1Score = 0;
// int player2Score = 0;
// int movement_vector[] = {-1,1,0};

// int asciiToKeyCode(char ascii) {
//     switch (ascii) {
//         case 0x1B: return 0x01;  // Escape
//         case 0x08: return 0x0E;  // Backspace
//         case 0x09: return 0x0F;  // Tab
//         case 0x0D: return 0x1C;  // Enter
//         case 0x00: return 0x1D;  // Left Ctrl
//         case ' ':  return 0x39;  // Space
        
//         case '1': return 0x02;
//         case '2': return 0x03;
//         case '3': return 0x04;
//         case '4': return 0x05;
//         case '5': return 0x06;
//         case '6': return 0x07;
//         case '7': return 0x08;
//         case '8': return 0x09;
//         case '9': return 0x0A;
//         case '0': return 0x0B;
//         case '-': return 0x0C;
//         case '=': return 0x0D;
//         case '[': return 0x1A;
//         case ']': return 0x1B;
//         case ';': return 0x27;
//         case '\'': return 0x28;
//         case '`': return 0x29;
//         case '\\': return 0x2B;
//         case ',': return 0x33;
//         case '.': return 0x34;
//         case '/': return 0x35;
        
//         case '^': return 0x48;  // Up arrow
//         case 'v': return 0x50;  // Down arrow
//         case '<': return 0x4B;  // Left arrow
//         case '>': return 0x4D;  // Right arrow
        
//         case 'A': return 0x1E;
//         case 'B': return 0x30;
//         case 'C': return 0x2E;
//         case 'D': return 0x20;
//         case 'E': return 0x12;
//         case 'F': return 0x21;
//         case 'G': return 0x22;
//         case 'H': return 0x23;
//         case 'I': return 0x17;
//         case 'J': return 0x24;
//         case 'K': return 0x25;
//         case 'L': return 0x26;
//         case 'M': return 0x32;
//         case 'N': return 0x31;
//         case 'O': return 0x18;
//         case 'P': return 0x19;
//         case 'Q': return 0x10;
//         case 'R': return 0x13;
//         case 'S': return 0x1F;
//         case 'T': return 0x14;
//         case 'U': return 0x16;
//         case 'V': return 0x2F;
//         case 'W': return 0x11;
//         case 'X': return 0x2D;
//         case 'Y': return 0x2C;
//         case 'Z': return 0x15;
        
//         default: return -1;  // Return -1 for unsupported characters
//     }
// }


// void setPlayer1Up(uint64_t key) {
//     player1Up = key;
//     player1Upbeak = key + 0x80;
// }

// void setPlayer1Down(uint64_t key) {
//     player1Down = key;
//     player1Downbeak = key + 0x80;
// }


// void setPlayer2Up(uint64_t key) {
//     player2Up = key;
//     player2Upbeak = key + 0x80;
// }

// void setPlayer2Down(uint64_t key) {
//     player2Down = key;
//     player2Downbeak = key + 0x80;
// }




// void drawPaddle(Paddle* paddle, uint64_t color) {
//     call_drawRectangle(color, paddle->x, paddle->y, paddle->width, paddle->height);
// }


// void clearPaddle(Paddle* paddle) {
//     drawPaddle(paddle, BACKGROUND_COLOR);
// }


// void clearBall() {
//     call_drawBall(BACKGROUND_COLOR, ball.size, ball.x, ball.y);
// }

// void movePaddle(Paddle* paddle) {
//     clearPaddle(paddle);
//     int move;
    
//     if (paddle->direction == UP) {
//         move = paddle->y - movement_vector[paddle->direction] * paddle->speed;
//         if (move >= BORDER_SIZE) {
//             paddle->y = move;
//         } else {
//             paddle->y = BORDER_SIZE;
//             paddle->direction = STOP;
//         }
//     } else if (paddle->direction == DOWN) {
//         move = paddle->y + paddle->speed;
//         if (move + paddle->height <= SCREEN_HEIGHT - BORDER_SIZE) {
//             paddle->y = move;
//         } else {
//             paddle->y = SCREEN_HEIGHT - BORDER_SIZE - paddle->height;
//             paddle->direction = STOP;
//         }
//     }
    
//     drawPaddle(paddle, paddle->color);
// }




// void showScoreCard(uint64_t hexColor){
//     //setFontSize(SCORE_CARD_FONT_SIZE);
//     //characterAt(hexColor, player1Score+'0', SCORE_CARD_X-30, SCORE_CARD_Y+50);
//     //characterAt(hexColor, player2Score+'0', SCORE_CARD_X+30, SCORE_CARD_Y+50);
// }
// void updateScore(int player){
//     if (player == 1){
//         //characterAt(BACKGROUND_COLOR, player1Score+'0', SCORE_CARD_X-30, SCORE_CARD_Y+50);
//         player1Score++;
//         //characterAt(WHITE, player1Score+'0', SCORE_CARD_X-30, SCORE_CARD_Y+50);
//     } else {
//         //characterAt(BACKGROUND_COLOR, player2Score+'0', SCORE_CARD_X+30, SCORE_CARD_Y+50);
//         player2Score++;
//         //characterAt(WHITE, player2Score+'0', SCORE_CARD_X+30, SCORE_CARD_Y+50);
//     }
// }
// void clearScoreCard(){
//     showScoreCard(BACKGROUND_COLOR);
// }

// char checkScored(){
//     if (ball.x + ball.size < paddle1.x + paddle1.width){
//         updateScore(2);
//         return 1;
//     }
//     if (ball.x - ball.size > paddle2.x){
//         updateScore(1);
//         return 1;
//     }
//     return 0;
// }       

// void moveBall() {
//     clearBall();
    
//     if (checkScored()) {
//         clearBall();
//         resetGame();
//         return;
//     }
    
//     ball.x += ball.speedX;
//     ball.y += ball.speedY;

//     if (ball.x <= BORDER_SIZE) {
//         ball.x = BORDER_SIZE;
//         ball.speedX = -ball.speedX;
//     } else if (ball.x + ball.size >= SCREEN_WIDTH - BORDER_SIZE) {
//         ball.x = SCREEN_WIDTH - BORDER_SIZE - ball.size;
//         ball.speedX = -ball.speedX;
//     }

//     if (ball.y <= BORDER_SIZE) {
//         ball.y = BORDER_SIZE;
//         ball.speedY = -ball.speedY;
//     } else if (ball.y + ball.size >= SCREEN_HEIGHT - BORDER_SIZE * 2) {
//         ball.y = SCREEN_HEIGHT - BORDER_SIZE * 2 - ball.size;
//         ball.speedY = -ball.speedY;
//     }

//     if (ball.x <= paddle1.x + paddle1.width && ball.x + ball.size >= paddle1.x && ball.y + ball.size >= paddle1.y && ball.y <= paddle1.y + paddle1.height){
//             ball.speedX *= -1;
//             if (paddle1.direction==UP)
//                 ball.speedY = -BALL_SPEED;
//             if (paddle1.direction==DOWN)
//                 ball.speedY = BALL_SPEED;
//             if (paddle1.direction==STOP)
//                 ball.speedY = 0;
//         }
//     if (ball.x + ball.size >= paddle2.x && ball.x <= paddle2.x + paddle2.width && ball.y + ball.size >= paddle2.y && ball.y <= paddle2.y + paddle2.height){
//             ball.speedX *= -1;
//             if (paddle2.direction==UP)
//                 ball.speedY = -BALL_SPEED;
//             if (paddle2.direction==DOWN)
//                 ball.speedY = BALL_SPEED;
//             if (paddle2.direction==STOP)
//                 ball.speedY = 0;
//         }

//     // if ((ball.x <= paddle1.x + paddle1.width && ball.x + ball.size >= paddle1.x && ball.y + ball.size >= paddle1.y && ball.y <= paddle1.y + paddle1.height) ||
//     //     (ball.x + ball.size >= paddle2.x && ball.x <= paddle2.x + paddle2.width && ball.y + ball.size >= paddle2.y && ball.y <= paddle2.y + paddle2.height)) {
//     //     if (ball.y >= paddle1.y + paddle1.height * (1.0 / 3.0) && ball.y <= paddle1.y + paddle1.height * (2.0 / 3.0)) {
//     //         // Ball hits the middle third of paddle1
//     //         ball.speedX *= -1;
//     //         ball.speedY *= 0;
//     //     } else if (ball.y < paddle1.y + paddle1.height * (1.0 / 3.0)) {
//     //         // Ball hits the top third of paddle1
//     //         ball.speedX *= -1;
//     //         ball.speedY = -BALL_SPEED;
//     //     } else {
//     //         // Ball hits the bottom third of paddle1
//     //         ball.speedX *= -1;
//     //         ball.speedY = BALL_SPEED;
//     //     }
//     // }

//     call_drawBall(ball.color, ball.size, ball.x, ball.y);
// }
// // #include <math.h>
// // void moveBall() {
// //     clearBall();

// //     if (checkScored()) {
// //         clearBall();
// //         resetGame();
// //         return;
// //     }

// //     ball.x += ball.speedX;
// //     ball.y += ball.speedY;

// //     if (ball.x <= BORDER_SIZE) {
// //         ball.x = BORDER_SIZE;
// //         ball.speedX = -ball.speedX;
// //     } else if (ball.x + ball.size >= SCREEN_WIDTH - BORDER_SIZE) {
// //         ball.x = SCREEN_WIDTH - BORDER_SIZE - ball.size;
// //         ball.speedX = -ball.speedX;
// //     }

// //     if (ball.y <= BORDER_SIZE) {
// //         ball.y = BORDER_SIZE;
// //         ball.speedY = -ball.speedY;
// //     } else if (ball.y + ball.size >= SCREEN_HEIGHT - BORDER_SIZE * 2) {
// //         ball.y = SCREEN_HEIGHT - BORDER_SIZE * 2 - ball.size;
// //         ball.speedY = -ball.speedY;
// //     }

// //     if ((ball.x <= paddle1.x + paddle1.width && ball.x + ball.size >= paddle1.x && ball.y + ball.size >= paddle1.y && ball.y <= paddle1.y + paddle1.height) ||
// //         (ball.x + ball.size >= paddle2.x && ball.x <= paddle2.x + paddle2.width && ball.y + ball.size >= paddle2.y && ball.y <= paddle2.y + paddle2.height)) {
// //         if (ball.y >= paddle1.y + paddle1.height * (1.0 / 3.0) && ball.y <= paddle1.y + paddle1.height * (2.0 / 3.0)) {
// //             // Ball hits the middle third of paddle1
// //             float magnitude = sqrt(ball.speedX * ball.speedX + ball.speedY * ball.speedY);
// //             float direction = atan2(ball.speedY, ball.speedX);
// //             ball.speedX = -magnitude * cos(direction);
// //             ball.speedY = magnitude * sin(direction);
// //         } else if (ball.y < paddle1.y + paddle1.height * (1.0 / 3.0)) {
// //             // Ball hits the top third of paddle1
// //             ball.speedX = -ball.speedX;
// //             ball.speedY = -BALL_SPEED;
// //         } else {
// //             // Ball hits the bottom third of paddle1
// //             ball.speedX = -ball.speedX;
// //             ball.speedY = BALL_SPEED;
// //         }
// //     }

// //     call_drawBall(WHITE);
// // }




// void resetGame() {
//     clearPaddle(&paddle1);
//     clearPaddle(&paddle2);

//     ball.x = SCREEN_WIDTH / 2 - ball.size / 2; 
//     ball.y = SCREEN_HEIGHT / 2 - ball.size / 2;

//     ball.speedX *= -1;
//     ball.speedY = 0;

//     paddle1.y = SCREEN_HEIGHT / 2 - paddle1.height / 2;
//     paddle2.y = SCREEN_HEIGHT / 2 - paddle2.height / 2;

//     drawPaddle(&paddle1, paddle1.color);
//     drawPaddle(&paddle2, paddle2.color);
// }

// void drawMiddleLine(){
//     for (int i = 0; i < SCREEN_HEIGHT; i+= 20){
//         call_drawRectangle(WHITE, SCREEN_WIDTH/2-5, i, 10, 10);
//     }
// }



// void drawBorders() {
//     call_drawRectangle(WHITE, 0, 0, SCREEN_WIDTH, BORDER_SIZE); 
//     call_drawRectangle(WHITE, 0, SCREEN_HEIGHT - BORDER_SIZE, SCREEN_WIDTH, BORDER_SIZE);  
// }
// void pauseModular(uint64_t hexColor){
//     //setFontSize(18);
//     //drawWordColorAt(hexColor, "PAUSED", SCREEN_WIDTH/2-270, SCREEN_HEIGHT/2-200);
//     //setFontSize(DEFAULT_FONT_SIZE);
//     //drawWordColorAt(hexColor, "Press X to exit. ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+100);
//     //drawWordColorAt(hexColor, "Press C to acces configuration. ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+130);
//     //drawWordColorAt(hexColor, "Press any other key to continue.", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2+160);
// }

// void pauseGame(){
//     pauseModular(WHITE);
// }
// void unpause(){
//     pauseModular(BACKGROUND_COLOR);
// }

// void training(Paddle* paddle2) {
//     if (ball.y + ball.size < paddle2->y + paddle2->height / 2) {
//         paddle2->direction = UP;
//     } else if (ball.y > paddle2->y + paddle2->height / 2) {
//         paddle2->direction = DOWN;
//     } else {
//         paddle2->direction = STOP;
//     }

//     movePaddle(paddle2);
// }

// // int benchmark(){
// //     int ticks = ticks_elapsed();
// //     for (long i = 0; i < 1000000000; i++);
// //     int ticks2 = ticks_elapsed();
// //     return ticks2-ticks;
// // }

// void sleepbm(int bm){
//     for (long i = 0; i < 70000000;i+=bm);
// }
// void options() {
//     //drawWordColorAt(WHITE, "CONFIGURATION", SCREEN_WIDTH/2-270, 0);
//     //drawWordColorAt(WHITE, "Press 1 to change the ball speed", 0, 30);
//     //drawWordColorAt(WHITE, "Press 2 to change the paddle speed", 0, 60);
//     //drawWordColorAt(WHITE, "Press 3 to change the experimental refresh rate", 0, 90);
//     //drawWordColorAt(WHITE, "Press 4 to change the ball size", 0, 120);
//     //drawWordColorAt(WHITE, "Press 5 to change the paddle size", 0, 150);
//     //drawWordColorAt(WHITE, "Press 6 to change the paddle height", 0, 180);
//     //drawWordColorAt(WHITE, "Press 7 to change the paddle width", 0, 210);
//     //drawWordColorAt(WHITE, "Press 8 to change the ball color", 0, 240);
//     //drawWordColorAt(WHITE, "Press 9 to change the paddle color", 0, 270);
//     //drawWordColorAt(WHITE, "Press 0 to change the background color", 0, 300);
//     //drawWordColorAt(WHITE, "Press C to change the keybinds of P1", 0, 330);
//     //drawWordColorAt(WHITE, "Press K to change the keybinds of P2", 0, 360);
//     //drawWordColorAt(WHITE, "Press X to exit", 0, 390);
// }


// int getNumber(){
//     char c;
//     int number = 0;
//     call_sys_read(&c, 1, 0);
//     int i = 0;
//     while (c != '\n') {
//         call_sys_read(&c, 1, 0);
//         if (c >= '0' && c <= '9') {
//             number = number * 10 + (c - '0');
//             //characterAt(WHITE, c, SCREEN_WIDTH/2 + i, SCREEN_HEIGHT/2+50); 
//             i+=16;
//         }
//     }
//     return number;
// }

// #define NUM_COMMON_COLORS 10

// uint64_t COMMON_COLORS[NUM_COMMON_COLORS] = {
//     0xFFFFFF,  // White
//     0x000000,  // Black
//     0xFF0000,  // Red
//     0x00FF00,  // Green
//     0x0000FF,  // Blue
//     0xFFFF00,  // Yellow
//     0xFF00FF,  // Magenta
//     0x00FFFF,  // Cyan
//     0x808080,  // Gray
//     0xFFA500   // Orange
// };


// void showColorOptions() {
//     //drawWordColorAt(WHITE, "Choose a color:", 0, 80);

//     for (int i = 0; i < NUM_COMMON_COLORS; i++) {
//         uint64_t color = COMMON_COLORS[i];
//         ////drawNumberColorAt(WHITE, i+1, 0, 80 + (i * 30));
//         call_put_square(SCREEN_WIDTH/2 + 40, 80 + (i * 30) - 10, 20, color);
//     }
// }


// void configuration(){
//     char c;
//     options();
//    while (1) {
//         options();
//         call_sys_read(&c, 1, 0);
//         switch (c) {
//             case '1': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current ball speed: ", 0, SCREEN_HEIGHT/2);
//                 ////drawNumberColorAt(WHITE, ball.speedX, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new ball speed: ", 0, SCREEN_HEIGHT/2+50);
//                 int speed = getNumber();
//                 //drawNumberColor( speed, WHITE);
//                 if (speed > 0) {
//                     ball.speedX = speed;
//                 }
//                 break;
//             }
//             case '2': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current paddle speed: ", 0, SCREEN_HEIGHT/2);
//                 ////drawNumberColorAt(WHITE, paddle1.speed, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new paddle speed: ", 0, SCREEN_HEIGHT/2+50);
//                 int speed = getNumber();
//                 if (speed > 0) {
//                     paddle1.speed = speed;
//                     paddle2.speed = speed;
//                 }
//                 break;
//             }
//             case '3': {

//                 break;
//             }
//             case '4': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current ball size: ", 0, SCREEN_HEIGHT/2);
//                 ////drawNumberColorAt(WHITE, ball.size, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new ball size: ", 0, SCREEN_HEIGHT/2+50);
//                 int size = getNumber();
//                 if (size > 0) {
//                     ball.size=size;
//                 }
//                 break;
//             }
//             case '5': {
                
//             }
//             case '6': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current paddle height: ", 0, SCREEN_HEIGHT/2);
//                 ////drawNumberColorAt(WHITE, paddle1.height, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new paddle height: ", 0, SCREEN_HEIGHT/2+50);
//                 int height = getNumber();
//                 if (height > 0) {
//                     paddle1.height = height;
//                     paddle2.height = height;

//                 }
//                 break;
//             }
//             case '7': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current paddle width: ", 0, SCREEN_HEIGHT/2);
//                 ////drawNumberColorAt(WHITE, paddle1.width, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new paddle width: ", 0, SCREEN_HEIGHT/2+50);
//                 int width = getNumber();
//                 if (width > 0) {
//                     paddle1.width = width;
//                     paddle2.width = width;
//                 }
//                 break;
//             }
//             case '8': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current ball color: ", 0, 0);
//                 call_put_square(SCREEN_WIDTH/2, 0, 20, BALL_COLOR);
//                 //drawWordColorAt(WHITE, "Enter the new ball color (1-10): ", 0, 50);
//                 showColorOptions();
//                 int color = getNumber(); //cambiar a getColor
//                 if (color >= 1 && color <= 10) {
//                     ball.color = COMMON_COLORS[color-1];
//                 }
//                 break;
//             }
//             case '9': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current paddle color: ", 0, 0);
//                 call_put_square(SCREEN_WIDTH/2, 0, 20, PADDLE_COLOR);
//                 //drawWordColorAt(WHITE, "Enter the new paddle color (1-10): ", 0, 50);
//                 showColorOptions();
//                 int color = getNumber();
//                 if (color >= 1 && color <= 10) {
//                     paddle1.color = COMMON_COLORS[color-1];
//                     paddle2.color = COMMON_COLORS[color-1];
//                 }
//                 break;
//             }
//             case '0': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current background color: ", 0, 0);
//                 call_put_square(SCREEN_WIDTH/2, 0, 20, BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Enter the new background color (1-10): ", 0, 50);
//                 showColorOptions();
//                 int color = getNumber();
//                 if (color >= 1 && color <= 10) {
//                     BACKGROUND_COLOR = COMMON_COLORS[color-1];
//                 }
//                 break;
//             }
//             case 'X': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 return;
//             }
//             case 'C': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current up key ", 0, SCREEN_HEIGHT/2);
//                 //characterAt(WHITE, ScanCodes[player1Up], SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new up key: ", 0, SCREEN_HEIGHT/2+50);
//                 char c;
//                 call_sys_read(&c, 1, 0);
//                 if (c != 0) {
//                     setPlayer1Up(asciiToKeyCode(c));
//                 }
//                 //characterAt(WHITE, c, SCREEN_WIDTH/2, SCREEN_HEIGHT/2+50);

//                 //drawWordColorAt(WHITE, "Current down key ", 0, SCREEN_HEIGHT/2+100);
//                 //characterAt(WHITE, ScanCodes[player1Down], SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);
//                 //drawWordColorAt(WHITE, "Enter the new down key: ", 0, SCREEN_HEIGHT/2+150);
//                 call_sys_read(&c, 1, 0);
//                 if (c != 0) {
//                     setPlayer1Down(asciiToKeyCode(c));
//                 }
//                 //characterAt(WHITE, c, SCREEN_WIDTH/2, SCREEN_HEIGHT/2+150);

//                 break;
//             }
//             case 'K': {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //drawWordColorAt(WHITE, "Current UP key ", 0, SCREEN_HEIGHT/2);
//                 //characterAt(WHITE, ScanCodes[player2Up], SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//                 //drawWordColorAt(WHITE, "Enter the new up key: ", 0, SCREEN_HEIGHT/2+50);
//                 char c;
//                 call_sys_read(&c, 1, 0);
//                 if (c != 0) {
//                     setPlayer2Up(asciiToKeyCode(c));
//                 }
//                 //characterAt(WHITE, c, SCREEN_WIDTH/2, SCREEN_HEIGHT/2+50);

//                 //drawWordColorAt(WHITE, "Current down key ", 0, SCREEN_HEIGHT/2+100);
//                 //characterAt(WHITE, ScanCodes[player2Down], SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);
//                 //drawWordColorAt(WHITE, "Enter the new down key: ", 0, SCREEN_HEIGHT/2+150);
//                 call_sys_read(&c, 1, 0);
//                 if (c != 0) {
//                     setPlayer2Down(asciiToKeyCode(c));
//                 }
//                 //characterAt(WHITE, c, SCREEN_WIDTH/2, SCREEN_HEIGHT/2+150);

//                 break;
//             }
//             default: {
//                 break;
//             }
//         }
//         call_clearColor(BACKGROUND_COLOR);
//    }
// }



// setPaddle(Paddle *paddle, int x, int y, int width, int height, int speed, char directon, uint64_t color) {
//     paddle->x = x;
//     paddle->y = y;
//     paddle->width = width;
//     paddle->height = height;
//     paddle->speed = speed;
//     paddle->direction = directon;
//     paddle->color = color;

// }
Ball ball;
setBall(int x, int y, int size, int speedX, int speedY, uint64_t color) {
    ball.x = x;
    ball.y = y;
    ball.size = size;
    ball.speedX = speedX;
    ball.speedY = speedY;
    ball.color = color;
}


// void Pong() {
    
//     setPaddle( &paddle1, 50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, STOP, WHITE);
//     setPaddle( &paddle2, SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, STOP, WHITE);
//     setBall(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SPEED, BALL_SPEED, WHITE);
//     setPlayer1Up(0x11);
//     setPlayer1Down(0x1F);
//     setPlayer2Up(0x48);
//     setPlayer2Down(0x50);
//     int experimental = 0;
//     int setting = 0;
   
//     //setFontSize(24);
//     //drawWordColorAt(WHITE, "PONG", SCREEN_WIDTH/2-270, SCREEN_HEIGHT/2-200);
//     //setFontSize(DEFAULT_FONT_SIZE);
//     //drawWordColorAt(WHITE, "Press E to enable experimental refresh rate", 0, SCREEN_HEIGHT/2+100);
//     //drawWordColorAt(WHITE, "Press any other key for default refresh rate", 0, SCREEN_HEIGHT/2+130);
//     char e;
//     call_sys_read(&e, 1, 0);
//     //drawWordColorAt(BACKGROUND_COLOR, "Press E to enable experimental refresh rate", 0, SCREEN_HEIGHT/2+100);
//     //drawWordColorAt(BACKGROUND_COLOR, "Press any other key for default refresh rate", 0, SCREEN_HEIGHT/2+130);
//     if ( e == 'E'){
//         //drawWordColorAt(WHITE, "Wait until benchmark is complete...", 0, SCREEN_HEIGHT/2+100);
//         experimental = 1;
//         // setting = benchmark();
//         //drawWordColorAt(BACKGROUND_COLOR, "Wait until benchmark is complete...", 0, SCREEN_HEIGHT/2+100);
//     }
     
//     //drawWordColorAt(WHITE, "Press T for training", 0, SCREEN_HEIGHT/2+100);
//     //drawWordColorAt(WHITE, "Press C for configuration", 0, SCREEN_HEIGHT/2+130);
//     //drawWordColorAt(WHITE, "Press any other key to begin 2 player PONG: ",0, SCREEN_HEIGHT/2+160);
//     //drawWordColorAt(WHITE, "Player 1 goes up with \"W\" and down with \"S\"",0, SCREEN_HEIGHT/2+190);
//     //drawWordColorAt(WHITE, "Player 2 goes up with \"^\" and down with \"v\"",0, SCREEN_HEIGHT/2+220);
//     int Training = 0;
//     char t;
 
//     call_sys_read(&t, 1, 0);
//     if( t == 'C'){
//         call_clearColor(BACKGROUND_COLOR);
//         configuration();
//     }
//     if ( t == 'T'){
//         Training = 1;
//     }
//     uint16_t c;
//     char p = 0;
      
//     call_clearColor(BACKGROUND_COLOR);
//     drawBorders();
//     drawMiddleLine();  
//     drawPaddle(&paddle1, paddle1.color);  
//     drawPaddle(&paddle2, paddle2.color);
//     showScoreCard(WHITE);
//     int pos = call_getBufferPosition();
//     long k =0;
   
    
//     while (1) {
//         showScoreCard(WHITE);
//         if (c==0x19){
//             pauseGame();
//             call_sys_read(&p, 1, 0);
//             if (p == 'X'){
//                 //clear();
//                 return;
//             }
//             if (p == 'C'){
//                 call_clearColor(BACKGROUND_COLOR);
//                 configuration();
//             };
//             call_clearColor(BACKGROUND_COLOR);
//             drawBorders();
//             drawMiddleLine();
//             drawPaddle(&paddle1, paddle1.color);
//             drawPaddle(&paddle2, paddle2.color);
//             showScoreCard(WHITE);

//             unpause();
//         }
//         while (pos <= call_getBufferPosition()) {
//             c = call_getCharAt(pos++-1);
//             if (c == player1Up) {
//                 paddle1.direction = UP;
//             }
//             else if (c == player1Upbeak){
//                 if (paddle1.direction == UP)
//                     paddle1.direction = STOP; 
//             }  

//             else if (c == player1Down){ 
//                 paddle1.direction = DOWN;
//             }

//             else if (c == player1Downbeak){ 
//                 if (paddle1.direction == DOWN)
//                     paddle1.direction = STOP;
//             }
//             if (!Training){
//                  if (c == player2Up){
//                     paddle2.direction = UP;
//                 }
//                 else if (c == player2Upbeak){
//                     if (paddle2.direction == UP)
//                         paddle2.direction = STOP; 
//                 }   

//                 else if (c == player2Down)
//                     paddle2.direction = DOWN;

//                 else if (c == player2Downbeak){
//                     if (paddle2.direction == DOWN)
//                         paddle2.direction = STOP;
//                 }
//             }
//             }
//             if (Training){
//                 training(&paddle2);
//             }
//             movePaddle(&paddle1);
//             movePaddle(&paddle2);
//             moveBall();

//             if (player1Score >= 3 || player2Score >= 3) {
//                 call_clearColor(BACKGROUND_COLOR);
//                 //setFontSize(18);
//                 //setFontSize(DEFAULT_FONT_SIZE);
//                 //drawWordColorAt(WHITE, "GAME OVER", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-170);
//                 if(player1Score>player2Score){
//                     //drawWordColorAt(WHITE, "PLAYER 1 WINS", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-130);
//                 }
//                 else{
//                     //drawWordColorAt(WHITE, "PLAYER 2 WINS", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-130);
//                 }
//                 //drawWordColorAt(WHITE, "Press X to exit. ", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-100);
//                 //drawWordColorAt(WHITE, "Press any other key to play again.", SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-75);
//                 call_sys_read(&p, 1, 0);
//                 if (p == 'X'){
//                     //clear();
//                     return;
//                 }
//                // clear();
//                 player1Score = 0;
//                 player2Score = 0;
//                 resetGame();
//                 drawMiddleLine();
//             }
//             drawMiddleLine();
//             // if (experimental)
//             //     sleepbm(setting);
//             // else sleepms(1);
//     }
// }

void Pong(){
         setBall(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 50, 0, 0, RED);
         call_drawBall(ball.color, ball.x, 0, ball.size);
         call_put_square(200, 200, 200, GREEN);
       
         call_drawRectangle(WHITE, 0, 100, 400, 4);
           call_put_square(200, 200, 200, RED);
         call_drawRectangle(RED, 300, 300, 500, 30);
    
}