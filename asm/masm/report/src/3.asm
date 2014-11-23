;------------------------------------------------------------------------------
; 程序描述：
;
;   将 datasg 段中每个单词的前 4 个字母改为大写字母
;------------------------------------------------------------------------------
assume cs:codesg, ss:stacksg, ds:datasg

stacksg segment
	dw 0, 0, 0, 0, 0, 0, 0, 0
stacksg ends

datasg segment
	db '1. display     $'
	db '2. brows       $'
	db '3. replace     $'
	db '4. modify      $'
datasg ends

codesg segment

start:
	nop

	mov cx, 4h			; 使用 cx 寄存器作为循环变量
	mov si, 0h

;------------------------------------------------------------------------------
; 循环修改一行
;------------------------------------------------------------------------------
make_uppercase:
	; 转换单词
	mov ax, datasg
	push ax				; (a)
	mov ax, si
	push ax				; (o)
	mov ax, 3			; 跳过 3 个字符
	push ax				; (n)
	mov ax, 4			; 转换 4 个字符
	push ax				; (m)
	call update_str
	
	; 输出单词
	mov ax, datasg
	push ax				; (a)
	mov ax, si
	push ax				; (o)
	call print_str

	add si, 10h			; 处理下一个单词
	loop make_uppercase

	jmp terminate

;------------------------------------------------------------------------------
; 修改一个字符串的前 m 个字母为大写
;
;  调用参数： 字符串基地址(a)、字符串偏移地址(o)、跳过字符数(n)、转换数目(m)
;  修改寄存器： 无
;------------------------------------------------------------------------------
update_str:

update_str_prologue:
	push bp
	mov bp, sp

	push ds
	mov ds, [bp+10]
	push bx
	mov bx, [bp+8]
	
	push ax
	push cx

update_str_body:
	add bx, [bp+6]			; 跳过 n 个字符
	mov cx, [bp+4]			; 转换 m 个字符

update_str_loop:
	mov ax, [bx]

	; 判断该字符是否为小写字母
	cmp al, 61h
	jb update_str_loop_0
	cmp al, 7ah
	ja update_str_loop_0

	sub ax, 20h			; 将小写字母转换为大写

update_str_loop_0:
	mov [bx], ax
	inc bx
	loop update_str_loop

update_str_epilogue:
	pop cx
	pop ax
	pop bx
	pop ds
	pop bp
	ret 8

;------------------------------------------------------------------------------
; 打印一个字符串
;
;  调用参数： 字符串基地址(a)、字符串偏移地址(o)
;  修改寄存器： 无
;------------------------------------------------------------------------------
print_str:

print_str_prologue:
	push bp
	mov bp, sp
	push dx
	push ds
	mov dx, [bp+4]
	mov ds, [bp+6]
	push ax

print_str_body:
	mov ah, 09h
	int 21h

	; 同时输出换行
	mov al, 0dh
	mov dl, al
	mov ah, 02h
	int 21h
	mov al, 0ah
	mov dl, al
	mov ah, 02h
	int 21h

print_str_epilogue:
	pop ax
	pop ds
	pop dx
	pop bp
	ret 4

;------------------------------------------------------------------------------
; 结束程序执行
;
; 修改寄存器： ax
;------------------------------------------------------------------------------
terminate:
	mov ax, 4c00h
	int 21h

codesg ends

end start
