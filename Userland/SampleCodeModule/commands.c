#include "commands.h"
#include "UserSyscalls.h"
#include "stdint.h"
#include "utils.h"
#include "pong.h"


void __seek_command__(char * command){
    

    for (int i = 0; i < COMMAND_LEN; i++){
        if (strcmpspace(command_list[i],command) == 0){
                __call_command__(i, command);
                return;
        }
    }
    __call_command__(-1, command);
}

void __call_command__(int i, char * command){
    switch (i)
    {
    case HELP:;
        help();
        return;
    case TIME:;
        time();
        return;
    case REG_STATE:;
        call_regState();
        return;
    case PONG:;
        Pong();    
        return;
    case SETCOLOR:;
        setbg(command);
        return;
    case DIV0:;
        Div0();
        return;
    case INVALOP:;
        invalidOp();
        return;
    default:;
        call_sys_write("ERROR - Comando no reconocido",30,2);
        putC('\n');
        return;
    }
}

void help(){
    call_sys_write("Lista de commandos disponibles:\n", 34,1);
    for (int i = 0; i < COMMAND_LEN; i++){
        call_sys_write(command_list[i],40,1);
        call_sys_write("\n",1,1);
    }
}

void time(){
    char timeClock[50];
    call_timeClock(timeClock);
    char c;
    for (int i = 0; (c = timeClock[i]) != 0; i++){
        putC(c);
    }
    putC('\n');
}


void setbgEnum(int i){
    switch (i){
        case RED_:; call_paintScreen(RED);
            return;
        case GREEN_:; call_paintScreen(GREEN);
            return;
        case BLUE_:; call_paintScreen(BLUE);
            return;
        case WHITE_:; call_paintScreen(WHITE);
            return;
        case BLACK_: ;call_paintScreen(BLACK);
            return;
        case YELLOW_: ;call_paintScreen(YELLOW);
            return;
        case ORANGE_:; call_paintScreen(ORANGE_);
            return;
        case BOKE_: call_boke();
            return;    
        default:
            return;
    }
}

void findColor(char * color){
    
   
    for (int i = 0; i < COMMAND_LEN; i++){
        if (strcmp(hexArr[i],color) == 0){
                setbgEnum(i);
                return;
        }
    }
    setbgEnum(-1);
}

void setbg(char * command){
    char partition[20];
    int i=0;
    for (i; !null_or_space(command[i]); i++);
    i++;
    int j = 0;
    for (i; command[i] != NULL; i++){
        partition[j++]=command[i];
    }
    partition[j]=0;
    findColor(partition);
    putC('\n');
}
void Div0(){
    int a = 0;
    int b = 1;
    int c = b/a;
}
void invalidOp(){
    invalidOpAsm();
}