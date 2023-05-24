#include "utils.h"
#include "UserSyscalls.h"
#define COMMAND_LEN 6
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define YELLOW 0xFFFF00
#define ORANGE 0xFFA500

static char hexArr[COLOR_LEN][10] = {"RED","GREEN","BLUE","WHITE","BLACK","YELLOW","ORANGE","BOKE"};

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
static char command_list[COMMAND_LEN][10] = {"HELP", "TIME", "REGSTATE","PONG", "SETCOLOR"};

static char command_list[COMMAND_LEN][10] = {"HELP", "TIME", "REGSTATE","PONG", "DIV0", "INVALOP"};

void __seek_command__(char * command);
void __call_command__(int i, char * command);
void help();
void time();
void setbg(char * command);
void setbgEnum(int i);
void findColor(char * color);
void call_boke();
void Div0();
void invalidOp();
