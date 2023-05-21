GLOBAL test

section .text

test:
mov rdi, 1
mov rsi, msg
mov rdx, len
mov rcx, 1
int 80h
mov rdi, 2
mov rsi, buff
mov rdx, 10
mov rcx, 0
int 80h
mov rdi, 1
mov rsi, buff
mov rdx, len
mov rcx, 1
int 80h
ret


section .data
msg db "TEST 123", 10, 0
len equ $-msg 
buff resb 100

