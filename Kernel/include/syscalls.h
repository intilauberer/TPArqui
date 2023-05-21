#ifndef _SYSCALLS_H
#define _SYSCALLS_H

void sys_write(const char *buf, int len, int filedescriptor);
void sys_read( char *buf, int len, int filedescriptor);


#endif