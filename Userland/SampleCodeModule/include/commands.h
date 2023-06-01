#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "utils.h"
#include "UserSyscalls.h"
#define COMMAND_LEN 7
#define COLOR_LEN 8
#define RED 0xFF00000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define YELLOW 0xFFFF00
#define ORANGE 0xFFA500



enum Commands {
    HELP,
    TIME,
    REG_STATE,
    PONG,
    SETCOLOR,
    DIV0,
    INVALOP
};
enum Colors {
    RED_,
    GREEN_,
    BLUE_,
    WHITE_,
    BLACK_,
    YELLOW_,
    ORANGE_,
    BOKE_
};



void __seek_command__(char * command); //Busca el comando ingresado por el usuario
void __call_command__(int i, char * command); //Llama al comando ingresado por el usuario
void help(); //Imprime la lista de comandos
void time(); //Imprime la hora actual
void setbg(char * command); //Cambia el color de fondo de la pantalla
void setbgEnum(int i); 
void findColor(char * color); //Busca el color ingresado por el usuario
void call_boke(); 
void Div0(); //Divide por 0 y genera una excepcion
void invalidOp(); //Genera una excepcion de operacion invalida

#endif /*__COMMANDS_H__*/