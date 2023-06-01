#include <stdin.h>
#include <buffer.h>
void clearBuffer(){
    for (int i = 0; i < BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
}
