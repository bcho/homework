;------------------------------------------------------------------------------
; 程序描述：
;
;   格式化输出 Power idea 公司从 1975 年到 1995 年的收入情况
;
;   TODO
;   - fix address loading
;   - fix table filling (make it right align)
;------------------------------------------------------------------------------
assume cs:codesg, ds:datasg

datasg segment
	; 年份信息 :0000h
	db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
	db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
	db '1993', '1994', '1995'

	; 收入信息 :0054h
	dd 16,	   22,	   382,	   1356,   2390,   8000,   16000,  24486,  50065
	dd 97479,  1401417,197514, 345980, 590827, 803530, 1183000, 1843000, 2759000
	dd 3753000,4649000,5937000

	; 雇员人数信息 :00a8h
	dw 3,	   7,	   9,	   13,	   28,	   38,	   130,    220,    476
	dw 778,    1001,   1442,   2258,   2793,   4037,   5635,   8226,   11542
	dw 14430,  15257,  17800
datasg ends

table segment
	; 每行信息
	db '    ', 09h, '    ', 09h, '     ', 09h, '          ', 09h, '$'
	line_break db 13, 10, '$'
table ends

codesg segment

start:
	nop

	mov cx, 16h
	mov si, 0

main:
	mov ax, datasg
	mov ds, ax
	call print_year
	inc si
	loop main
	
	jmp terminate

;------------------------------------------------------------------------------
; 打印一个年份的信息
;
;   参数：数据段基地址（ds） 位移数（si）
;   返回：无
;   改变寄存器：无
;------------------------------------------------------------------------------
print_year:

print_year_prologue:
	push dx
	push ds
	push ax
	push bx
	push cx

print_year_body:
	; 填充年份
	push si
	mov ax, datasg
	mov ds, ax
	mov ax, [0h+si]
	mov bx, 0
	call write_table
	mov ax, [2h+si]
	mov bx, 2
	call write_table
	pop si

	; 填充总收入
	mov ax, datasg
	mov ds, ax
	mov dx, [54h+si+2]
	mov ax, [54h+si]
	push ax
	mov ax, table
	mov ds, ax
	pop ax
	push si
	mov si, 5h
	call dtoc
	pop si

	; 填充员工数
	mov ax, datasg
	mov ds, ax
	mov dx, 0
	mov ax, [00a8h+si]
	push ax
	mov ax, table
	mov ds, ax
	pop ax
	push si
	mov si, 0eh
	call dtoc
	pop si

	; 计算平均收入
	mov ax, datasg
	mov ds, ax
	mov dx, [54h+si+2]
	mov ax, [54h+si]
	mov cx, [00a8h+si]
	call divdw
	; 保存平均收入
	push dx
	push ax
	
	; 填充员工平均收入
	mov ax, datasg
	mov ds, ax
	pop ax
	pop dx
	push ax
	mov ax, table
	mov ds, ax
	pop ax
	push si
	mov si, 14h
	call dtoc
	pop si

	mov ax, table
	mov ds, ax
	mov si, 18h
	mov ax, 24h
	mov [si], ax
	
	; 输出该行
	mov ax, table
	mov ds, ax
	mov dx, 0
	mov ah, 09h
	int 21h

	mov ax, table
	mov ds, ax 
	lea dx, line_break
	mov ah, 09h
	int 21h

print_year_epilogue:
	pop cx
	pop bx
	pop ax
	pop ds
	pop dx
	ret

;------------------------------------------------------------------------------
; 向 table 写入一个字节的数据
;
;   参数：table 段的偏移（bx） 写入数据（ax）
;   返回：无
;   改变寄存器：无
;------------------------------------------------------------------------------
write_table:

write_table_prologue:
	push ds
	push si

write_table_body:
	mov si, table
	mov ds, si
	mov [bx], ax

write_table_epilogue:
	pop si
	pop ds
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
;   返回：无
;   改变寄存器：si 指向字符串最后一位
;------------------------------------------------------------------------------
dtoc:

dtoc_prologue:
	push dx
	push ax
	push bx
	push cx

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
	pop cx
	pop bx
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
