GLOBAL test

section .text

test:
mov rbx, 0x41
mov rcx, 0x59
mov rdi, 4      ;syscall deseada
int 80h
ret


section .data
msg db "TEST 123", 10, 0
len equ $-msg 
buff resb 100

