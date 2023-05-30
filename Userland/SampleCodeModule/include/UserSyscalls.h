#include "stdint.h"

#ifndef USERSYSCALLS_H
#define USERSYSCALLS_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void call_sys_read(char *buf, int size, int fd);
void call_sys_write(char *buf, int size, int fd);
void call_timeClock(char *buf);
void call_regState();
void call_paintScreen(uint64_t hex);
void call_boke();
// void call_drawRectangle(uint64_t color, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void call_drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void call_drawBall( uint64_t color, uint64_t x, uint64_t y, uint64_t size);
int call_getBufferPosition();
int call_getCharAt(int pos);
void call_put_square(uint32_t x, uint32_t y, uint32_t size, uint64_t hexColor);
#endif /* USERSYSCALLS_H */
