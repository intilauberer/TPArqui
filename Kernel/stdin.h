

#include <stdint.h>
typedef struct stdin_buffer* stdin_ptr; 

struct stdin_buffer { 
    char buff[128];
    int bufferPos;
    int bufferLen;
};

int getBufferPosition();
int setPos(int new_len);
int getBufferLen();
int setLen(int new_len);
char * getBufferAddress();
char getCharAt(int pos);
void setBuffNext(char c);