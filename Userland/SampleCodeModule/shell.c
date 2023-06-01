#include <shell.h>
#include <UserSyscalls.h>
#include <commands.h>
#include <stdin.h>
#include <buffer.h>




void lineRead(char * line){
    __seek_command__(line);
    // Morfar linea
    clearBuffer();
}

void putLineStart()
{   
    char s[] = "O] ";
    print(s);
    clearBuffer();
}

void bufferize (){
    
    int i = 0;
    int end_of_buffer = 0;
    while (i < BUFFER_SIZE) {
        char c = getC();
        end_of_buffer = (i == BUFFER_SIZE-1);
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
        } else{
            if (!end_of_buffer)
                buffer[i++] = c;
            else
                continue;}
        putC(c);
    }
    return;
}

void welcome(){
    call_paintScreen(BLACK);
    char WELCOME_MESSAGE[] = "Bienvenido a BOKE.\nIngrese un comando para continuar:\n(Ingrese HELP para ver todos los comandos)\n";
    for (int j=0; WELCOME_MESSAGE[j] != 0; j++){
        putC(WELCOME_MESSAGE[j]);
    }
}

int __shell_init__(){
    welcome();
    while (1){
        putLineStart();
        bufferize();
        call_sleepms(1);
    }
}



// Vuelve a principio de userland cuando se lanza excepcion
// RESTAURAR STACK

// MAPEAR TECLA A FOTO DE REGISTROS

// 