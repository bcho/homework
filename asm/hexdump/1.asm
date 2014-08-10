; This program is used to display a file with hex byte by byte.

section .bss

    BUFF_SIZE equ 16                ; buffer size
    BUFF resb BUFF_SIZE             ; declare a buffer in bss


section .data

    ; declare a buffer to write the hex line
    HEX_ORIGNAL_STR: db " 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00", 10
    HEX_STR: db " 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00", 10
    HEX_STR_SIZE equ $-HEX_STR

    DIGITS: db "0123456789ABCDEF"   ; characters table


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
    mov ebp, eax                ; store the return value (how many characters we had read)
    
    ; Check if the character is ``EOF``
    cmp eax, 0
    je exit                     ; reach EOF, job is finished

    ; Setup hex line buffer
    mov esi, BUFF               ; set buffer address
    mov edi, HEX_STR            ; set output buffer address
    xor ecx, ecx                ; set the character counter to 0
    
    ; jmp convert               ; starts converting


; Hexdump this line.
convert:

scan:

    ; Reset the output buffer.
    xor edx, edx                ; set counter to 0
    xor eax, eax                ; clear eax


; Reset output line.
reset:
    mov al, byte [HEX_ORIGNAL_STR+edx]
    mov byte [HEX_STR+edx], al
    inc edx
    cmp edx, HEX_STR_SIZE       ; reset finish?
    jl  reset                   ; copy next byte
    ; jmp translate             ; start translation


; Translate the character.
translate:
    xor eax, eax                ; clear eax
    xor edx, edx                ; clear edx

    ; Calculate the cell position in the ``BUFF``.
    ; Because each byte will use 3 characters to represent (space + hi + lo),
    ; so the first cell address ``3 * character counter + HEX_STR_ADDRESS``.
    mov edx, ecx
    shl edx, 1                  ; 2 * character counter
    add edx, ecx                ; 2 * character counter + character counter

    ; Separate the byte.
    mov al, byte [esi+ecx]      ; the low 4 bits
    mov ebx, eax                ; the high 4 bits

    ; Convert the lower bits.
    and eax, 0Fh                ; erase the high 4 bits
    mov al, byte [DIGITS+eax]   ; look up the character
    mov byte [edi+edx+2], al    ; write to the output buffer

    ; Convert the higher bits.
    shr ebx, 4                  ; erase the low 4 bits and move high 4 bits
    mov bl, byte [DIGITS+ebx]   ; look up the character
    mov byte [edi+edx+1], bl    ; write to the output buffer

    ; Process next character.
    inc ecx                     ; increase the character counter
    cmp ecx, ebp                ; reach the length?
    jna translate               ; process next one
    ; jmp write                 ; write the character


; Write the line.
write:
    mov eax, 4                  ; use ``sys_write`` here
    mov ebx, 1                  ; use fd:1 (stdout)
    mov ecx, HEX_STR            ; set buffer address
    mov edx, HEX_STR_SIZE       ; set print sequence length
    int 80h
    jmp read                    ; continue to next batch


exit:
    mov eax, 1                  ; use ``exit`` here
    mov ebx, 0                  ; set ret value
    int 80h
