section .data

    Snippet db "KANGAROO"

section .text

    global _start


_start:
    nop

    mov ebx, Snippet
    ; Loop counter
    mov eax, 8

DoMore:

    ; ``byte`` is a type hint.
    ; Convert the character to lowercase by adding 32.
    add byte [ebx], 20h
    ; Move to next byte
    inc ebx
    ; Decrease loop counter
    dec eax
    ; Loop condition
    jnz DoMore


    ; Init ``sys_write`` sys-call.
    mov eax, 4
    ; Ues ``stdout``.
    mov ebx, 1
    mov ecx, Snippet
    mov edx, 8
    ; Interrupt to print
    int 80h

    ; Init ``exit`` sys-call.
    mov eax, 1
    ; Exit 0.
    mov ebx, 0
    int 80H

    nop

section .bss
