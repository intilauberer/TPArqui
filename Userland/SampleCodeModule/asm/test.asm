GLOBAL test

section .text

test:
mov rax, 0x12345678
rdpmc
ret


section .data
msg db "TEST 123", 10, 0
len equ $-msg 
buff resb 100

