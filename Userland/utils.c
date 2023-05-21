#include <utils.h> //crear
#include <syscalls.h> 

//deben faltar mil cosas i know

char getChar(){
    char c;
    sys_read(&c, 1, STDIN);
}

void putChar(char c){
    sys_write(c, 1, STDOUT);
}

void scanf(char * buffer, uint64_t len){
 /*
    if(len == 0){
        return;
    }

    uint64_t count = 0; 
    do{
        char c = getChar();
        
    } while()
*/
}

