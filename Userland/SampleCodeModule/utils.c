#include <stdio.h>
#include <stdarg.h>
#include "utils.h"
#include "UserSyscalls.h"

//deben faltar mil cosas i know

char getC(){
    char c;
    call_sys_read(&c, 1, STDIN);
    return c;
}

void putC(char c){
    call_sys_write(&c, 1, STDOUT);
}

int own_scanf(char * format, ...){
    va_list args;
    va_start(args, format);
    int toRet = 0;

    while(*format != '\0'){

        if(*format == '%'){
            format++; 
            switch(*format){
                case 'c': {
                    char* c = va_arg(args, char*);
                    *c = getC();
                    toRet++;
                    break;
                }
                case 'd': {
                    int* d = va_arg(args, int*);
                    toRet += readInt(d);
                    break;
                }
                case 's': {
                    char* s = va_arg(args, char*);
                    toRet += readString(s);
                    break;
                }
                case 'x': {
                    int* d = va_arg(args, int*);
                    toRet += readHexInt(d);
                    break;
                }
                default: //?
                break;
            }
        }
        format++;
    }
    va_end(args);

    return toRet;
}

int readInt(int* d){
    int value = 0;
    int sign = 1; //en principio positivo
    char c = getC();

    if(c == '-'){
        sign = -1;
        c = getC();
    }

    while((c != '\0') && (c >= '0' && c <= '9')){
        value = (c - '0') + value*10;
        c = getC();
    }

    *d = value * sign;
    return 1;
}

int readString(char *s){
    int i = 0;
    char c = getC();

    while(c != '\0' && c != '\n'){
        s[i++] = c;
        c = getC();
    }
    s[i] = '\0'; //null terminated
    return i;
}

int readHexInt(int* d){
    int value = 0;
    int sign = 1;
    char c = getC();

    if(c == '-'){
        sign = -1;
        c = getC();
    }

    while(c != '\0' && ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))){
        if(c >= 'A' && c <= 'F'){
            c = c - 'A' + 10;
        }else{
            c = c - '0';
        }
        value = value * 16 + c;
        c = getC();
    }

    *d = value * sign;
    return 1;
}


//ACORDARSE IMPRIMIR TODO JUNTO O A MEDIDA QUE LEE??? SIGNO DE PREGUNTA.
//FALTA BASETOINT O ALGO QUE TRADUZCA AHRE

void print(const char * format, ...){
    va_list args;
    va_start(args, format);

    int len = 0;

    while(*format != '\0'){
        if(*format == '%'){
            format++;

            switch(*format){
                case 'c': {
                    char c = va_arg(args, char*);
                    putC(c);
                    break;
                }
                case 'd': {
                    int d = va_arg(args, int*);

                }
            }
        } else {
            putC(*format);
        }
        format++;
    }

    va_end(args);
    return;
}



