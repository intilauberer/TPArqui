#include "shell.h"
#include "UserSyscalls.h"
#include "commands.h"
#define STDIN 0
#define BUFFER_SIZE 128
char buffer[BUFFER_SIZE] = {0};

void clearBuffer(){
    for (int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
}

void lineRead(char * line){
    __seek_command__(line);
    // Morfar linea
    clearBuffer();
}

void putLineStart(){
    putC('O');
    putC(']');
    putC(' ');
    clearBuffer();
}

void bufferize (){
    putLineStart();
    int i = 0;
    while (i < BUFFER_SIZE) {
        char c = getC();
        
        if (c == '\b'){
            if ( i > 0)
                i--;
            else continue;
        } else if (c == '\n'){
            putC(c);
            if ( i == 0 ){
                clearBuffer();
                return;
            }
            buffer[i]=0;
            lineRead(buffer);
            return;
        } else
            buffer[i++] = c;
            putC(c);
    }
    return;
}
void welcome(){
    char * WELCOME_MESSAGE = "Bienvenido a BOKE.\nIngrese un comando para continuar:\n(Ingrese HELP para ver todos los comandos)\n";
    for (int j=0; WELCOME_MESSAGE[j] != 0; j++){
        putC(WELCOME_MESSAGE[j]);
    }
}

int __shell_init__(){
    welcome();
    while (1){
        bufferize();
    }
}



// Vuelve a principio de userland cuando se lanza excepcion
// RESTAURAR STACK

// MAPEAR TECLA A FOTO DE REGISTROS

// 