; helloworld.asm
; Hello, world!

SECTION .data

Msg: db "Hello, world", 10
MsgLen: equ $-Msg

SECTION .bss

SECTION .text

global _start

_start:
    nop
    mov eax, 4
    mov ebx, 1
    mov ecx, Msg
    mov edx, MsgLen
    int 80H
    mov eax, 1
    mov ebx, 0
    int 80H
