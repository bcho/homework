;------------------------------------------------------------------------------
; 程序描述：
;
;   格式化输出 Power Idea 公司从 1975 年到 1995 年的收入情况
;------------------------------------------------------------------------------
assume cs:codesg, ds:datasg

datasg segment
	; 年份信息 :0000h
	dd 1975,   1976,   1977,   1978,   1979,   1980,   1981,   1982,   1983
	dd 1984,   1985,   1986,   1987,   1988,   1989,   1990,   1991,   1992
	dd 1993,   1994,   1995

	; 收入信息 :0054h
	dd 16,	   22,	   382,	   1356,   2390,   8000,   16000,   24486,  50065
	dd 97479,  140417, 197514, 345980, 590827, 803530, 1183000, 1843000, 2759000
	dd 3753000,4649000,5937000

	; 雇员人数信息 :00a8h
	dd 3,	   7,	   9,	   13,	   28,	   38,	   130,    220,    476
	dd 778,    1001,   1442,   2258,   2793,   4037,   5635,   8226,   11542
	dd 14430,  15257,  17800

	number_buffer db '         $'
datasg ends


codesg segment

start:
	nop
	
	; 建立数据段
	mov ax, datasg
	mov ds, ax

	; 重复 21 次
	mov cx, 15h
	jcxz print_year_finish
print_year_loop:
	; 计算偏移
	mov di, 15h
	sub di, cx
	mov ax, 4
	mul di
	mov di, ax

	; 写入年份
	mov ax, datasg:[di+0]
	mov dx, datasg:[di+2]
	lea si, number_buffer 
	call dtoc
	call write_number_buffer

	; 写入制表符
	mov dl, 09h
	call write_char

	; 写入总收入
	mov ax, datasg:[0054h+di]
	mov dx, datasg:[0054h+di+2]
	lea si, number_buffer 
	call dtoc
	call write_number_buffer

	; 写入制表符
	mov dl, 09h
	call write_char
	
	; 写入雇员数
	mov ax, datasg:[00a8h+di]
	mov dx, 0h			; datasg:[00a8h+di+2]
	lea si, number_buffer 
	call dtoc
	call write_number_buffer
	
	; 写入制表符
	mov dl, 09h
	call write_char
	
	; 求平均收入
	mov ax, datasg:[0054h+di]
	mov dx, datasg:[0054h+di+2]
	push cx
	mov cx, datasg:[00a8h+di]
	call divdw
	pop cx
	; 写入平均收入
	lea si, number_buffer 
	call dtoc
	call write_number_buffer

	; 写入换行符
	mov dl, 0dh
	call write_char
	mov dl, 0ah
	call write_char

	loop print_year_loop		; 写入下一年的信息

print_year_finish:
	jmp terminate

;------------------------------------------------------------------------------
; 将 number_buffer 写入到终端（最多 8 位，右对齐）
;
;   参数： 字符串长度（bx）
;   返回：无
;   修改寄存器：无
;------------------------------------------------------------------------------
write_number_buffer:

write_number_buffer_prologue:
	push ax
	push ds
	push dx
	push cx
	push si

write_number_buffer_body:
	mov ax, datasg
	mov ds, ax
	lea si, number_buffer		; 字符下标
	mov cx, bx
	jcxz write_number_buffer_epilogue

write_number_buffer_str:		; 填充字符串
	mov dx, [si]
	call write_char
	inc si
	loop write_number_buffer_str

write_number_buffer_epilogue:
	pop si
	pop cx
	pop dx
	pop ds
	pop ax
	ret

;------------------------------------------------------------------------------
; 显示一个字符到终端
;
;   参数：显示字符（dl）
;   返回：无
;   改变寄存器：无
;------------------------------------------------------------------------------
write_char:

write_char_prologue:
	push ax

write_char_body:
	mov ah, 02h
	int 21h

write_char_epilogue:
	pop ax
	ret

;------------------------------------------------------------------------------
; dword 除法
;
;   参数：被除数（dx:ax） 除数（cx）
;   返回：商（dx:ax） 余数（cx）
;   改变寄存器：无
;------------------------------------------------------------------------------
divdw:

divdw_prologue:
	push si

divdw_body:
	; 计算 int(H/N), rem(H/N)
	mov si, ax
	mov ax, dx
	mov dx, 0
	div cx
	push ax				; 保存 int(H/N)

	; 计算 (rem(H/N) * 65536 + L) / N
	mov ax, si			; L
	div cx
	mov cx, dx			; 余数
	pop dx				; 结果高 16 位

divdw_epilogue:
	pop si
	ret


;------------------------------------------------------------------------------
; 将一个字转换成十进制字符串，以 '\0' 结尾
;
;   参数：待转换数字(dx:ax) 指向字符串首地址 (ds:si)
;   返回：bx 转换后的字符串长度
;   改变寄存器：无
;------------------------------------------------------------------------------
dtoc:

dtoc_prologue:
	push dx
	push ax
	push cx
	push si

dtoc_body:
	mov bx, 0h			; 记录位数

dtoc_div:
	mov cx, 0ah			; 每次除以 10
	call divdw
	push cx				; 保存余数
	inc bx
	cmp ax, 0

	; 判断被除数是否为 0
	jne dtoc_div
	cmp dx, 0
	jne dtoc_div

	mov cx, bx			; 将数字转换为字符
	; jmp dtoc_to_char

dtoc_to_char:
	pop ax
	add ax, 30h			; 转换为 ascii 字符
	mov [si], ax
	inc si
	loop dtoc_to_char
	mov ax, 0h			; 填充 0 结尾
	mov [si], ax
	
dtoc_epilogue:
	pop si
	pop cx
	pop ax
	pop dx
	ret

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
