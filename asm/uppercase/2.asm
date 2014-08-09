; This program will read characters from stdin and convert all
; lowercase characters (namely, a-z) to uppercase (namely, A-Z).

section .bss

    BUFF_SIZE equ 1024          ; buffer size
    BUFF resb BUFF_SIZE         ; declare a 1024-byte-long buffer in bss

section .data

section .text

    global _start


_start:
    nop


; Read from stdin.
read:
    mov eax, 3                  ; use ``sys_read`` here
    mov ebx, 0                  ; use fd:0 (stdin)
    mov ecx, BUFF               ; set buffer address
    mov edx, BUFF_SIZE          ; set buffer size, read at most BUFF_SIZE characters
    int 80h
    mov esi, eax                ; store the return value (how many characters)

    ; Check if the character is ``EOF``
    cmp eax, 0
    je exit                     ; reach EOF, job is finished

    ; Adjust buffer size base on the return value
    mov ecx, esi                ; indicates how many characters we got
    mov ebp, BUFF               ; set buffer address
    dec ecx                     ; off-by-1
    ; jmp convert               ; continue our job


; Convert buffer (by scan through the buffer).
convert:

; Scan through the buffer.
scan:
    ; Check if the character is in range [a-z]
    cmp byte [ebp+ecx], 61h     ; compare (first byte) with ``a``
    jb next                     ; c < 'a', we won't process this character
    cmp byte [ebp+ecx], 7Ah     ; compre (first byte) with ``z``
    ja next                     ; c > 'z', we won't process this character

    sub byte [ebp+ecx], 20h     ; convert this charater into uppercase
    ; jmp next                  ; continue the next character
   
; Process next byte.
next:
    dec ecx                     ; set index to previous byte
    cmp ecx, 0
    ja scan                     ; process next character


; Write to stdout.
write:
    mov eax, 4                  ; use ``sys_write`` here
    mov ebx, 1                  ; use fd:1 (stdout)
    mov ecx, BUFF               ; set buffer address
    mov edx, esi                ; set print sequence length
    int 80h
    jmp read                    ; continue to next character


exit:
    mov eax, 1                  ; use ``exit`` here
    mov ebx, 0                  ; set ret value
    int 80h
