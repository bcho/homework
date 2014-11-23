;------------------------------------------------------------------------------
; 程序描述：
;
;   输出从 0x010 到 0x100 范围内的 ascii 码表（16 个一行）
;------------------------------------------------------------------------------
assume ds:datasg, cs:codseg

datasg segment

	; 以行为输出单位
	line_buffer db 00, " ", 00, " ", 00, " ", 00, " ", 00, " ", 00, " ", \
		       00, " ", 00, " ", 00, " ", 00, " ", 00, " ", 00, " ", \
		       00, " ", 00, " ", 00, " ", 00, 13, 10, 13, 10, "$"

datasg ends


codseg segment

start:
	nop

	; 使用 si 寄存器作为行循环变量
	mov si, 10h

;------------------------------------------------------------------------------
; 循环填充各行
;
; 修改寄存器：si
;------------------------------------------------------------------------------
fill_lines:

	call fill_line                  ; 填充当前行
	call print_line                 ; 输出当前行

        cmp si, 100h
	jb fill_lines                   ; 继续填充下一行

	jmp terminate                   ; 结束程序

;------------------------------------------------------------------------------
; 填充缓冲行
;
; 修改寄存器：si
;------------------------------------------------------------------------------
fill_line:

fill_line_prologue:
	push bx
	push cx
	push ds
	push dx

fill_line_main:
	; 准备缓冲行地址到 ds:dx 段中
	mov ax, datasg
	mov ds, ax
	lea dx, line_buffer
	; 准备循环变量
	mov bx, 0h                      ; 缓冲行修改单元下标
	mov cx, 10h                     ; 循环变量

fill_line_loop:
	mov [bx], si                    ; 将当前 ascii 字符填充到输出行中
	inc si                          ; ascii 字符增加 1
	add bx, 2                       ; 缓冲行单元下标增加 2（跳过空格）
	loop fill_line_loop

fill_line_epilogue:
	pop dx
	pop ds
	pop cx
	pop bx
	ret

;------------------------------------------------------------------------------
; 打印缓冲行
;
; 修改寄存器：无
;------------------------------------------------------------------------------
print_line:

print_line_prologue:
	push ax
	push ds
	push dx

print_line_body:
	; 准备缓冲行地址到 ds:dx 段中
	mov ax, datasg
	mov ds, ax
	lea dx, line_buffer
	mov ah, 09h
	int 21h

print_line_epilogue:
	pop dx
	pop ds
	pop ax
	ret

;------------------------------------------------------------------------------
; 结束程序执行
;
; 修改寄存器： ax
;------------------------------------------------------------------------------
terminate:
	mov ax, 4c00h
	int 21h

codseg ends

end start
