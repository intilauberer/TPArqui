

#include <stdint.h>
#define BUFF_SIZE 4096
typedef struct stdin_buffer* stdin_ptr; 

struct stdin_buffer { 
    int bufferPos;
    int bufferLen;
    char buff[BUFF_SIZE];
};

int getBufferPosition();
int setPos(int new_len);
int getBufferLen();
int setLen(int new_len);
char * getBufferAddress();
char getCharAt(int pos);
void cleanBuffer();
void consumeBuffAt(int pos);