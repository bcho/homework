; Store named data
; Init when program starts running
section .data

Msg: db "Hello, world!"

; Store on the compiled program?
section .text

    global _start

_start:
    nop
    ; Real program goes after here... 

    ; op dest, src
    ; Use `(i)nfo (r)egister [register]` to inspect regs.
    mov eax, 42h
    ; It's big endian
    mov edx, [Msg]
    mov ecx, Msg

    nop

; Store uninitiated data.
; Stays after .text
section .bss
