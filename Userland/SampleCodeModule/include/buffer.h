#ifndef __BUFFER_H__
#define __BUFFER_H__
#define STDIN 0
#define BUFFER_SIZE 128

void clearBuffer();

static char buffer[BUFFER_SIZE] = {0};

#endif /* __BUFFER_H__ */