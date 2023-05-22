#include "stdin.h"
#include "defs.h"
static struct stdin_buffer buff = { {'\0'}, 0, 0 };

static stdin_ptr ptr = &buff;

int getBufferPosition(){
    return ptr->bufferPos;
}
int setPos(int new_pos){
    ptr->bufferPos = new_pos;
    return new_pos;
}

int getBufferLen(){
    return ptr->bufferLen;
}
int setLen(int new_len){
    ptr->bufferLen = new_len;
    return new_len;
}

char * getBufferAddress(){
    return ptr->buff;
}

char getCharAt(int pos){
    return ptr->buff[pos];
}


void setBuffNext(char c){
    ptr->buff[ptr->bufferPos]=c;
}
