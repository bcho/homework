; This program will read characters from stdin one by one and convert all
; lowercase characters (namely, a-z) to uppercase (namely, A-Z).

section .bss

    buff resb 1                 ; declare a 1-byte-long buffer in bss

section .data


section .text
    
    global _start


_start:
    nop

; Read a character from stdin.
read:
    ; Read a character:
    mov eax, 3                  ; use ``sys_read`` here
    mov ebx, 0                  ; use fd:0 (stdin)
    mov ecx, buff               ; set buffer address
    mov edx, 1                  ; read one character
    int 80h
    
    ; Check if the character is ``EOF``
    cmp eax, 0
    je exit                     ; reach EOF, job is finished
    ; jmp convert               ; continue our job

; Convert a lowercase character ([a-z]) to uppercase ([A-Z])
convert:
    ; Check if the character is in range [a-z]
    cmp byte [buff], 61h        ; compare (first byte) with ``a``
    jb write                    ; c < 'a', we won't process this character
    cmp byte [buff], 7Ah        ; compre (first byte) with ``z``
    ja write                    ; c > 'z', we won't process this character

    sub byte [buff], 20h        ; convert this charater into uppercase
    ; jmp write                 ; write the character

write:
    mov eax, 4                  ; use ``sys_write`` here
    mov ebx, 1                  ; use fd:1 (stdout)
    mov ecx, buff               ; set buffer address
    mov edx, 1                  ; set print sequence length
    int 80h
    jmp read                    ; continue to next character

exit:
    mov eax, 1                  ; use ``exit`` here
    mov ebx, 0                  ; set ret value
    int 80h
