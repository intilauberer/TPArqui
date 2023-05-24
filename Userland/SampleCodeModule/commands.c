#include "commands.h"
#include "UserSyscalls.h"
void __seek_command__(char * command){
    int i = 0;
    for (i; i < COMMAND_LEN; i++){
        if (strcmp(command, command_list[i]) == 0){
                __call_command__(i);
                return;
        }
    }
    __call_command__(-1);
}

void __call_command__(int i){
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
        return;
    default:;
        call_sys_write("ERROR - Comando no reconocido",50,2);
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