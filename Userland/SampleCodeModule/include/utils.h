#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>

// Function declarations

char getChar();
void putChar(char c);
int scanf(char * format, ...);
int readInt(int* d);
int readString(char *s);
int readHexInt(int* d);

#endif // UTILS_H
