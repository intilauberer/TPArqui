#include "utils.h"
#include "UserSyscalls.h"
#define COMMAND_LEN 4
#define WHITE 0xFFFFFF
enum Commands {
    HELP,
    TIME,
    REG_STATE,
    PONG
};

static char command_list[COMMAND_LEN][10] = {"HELP", "TIME", "REGSTATE","PONG"};

void __seek_command__(char * command);
void __call_command__(int i);
void help();
void time();