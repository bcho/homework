assume cs:code

a segment
	db 1, 2, 3, 4, 5, 6, 7, 8
a ends

b segment
	db 1, 2, 3, 4, 5, 6, 7, 8
b ends

c segment
	db 0, 0, 0, 0, 0, 0, 0, 0
c ends

code segment

start:
	mov ax, c
	mov ds, ax		; 建立结果的段空间

	mov bx, 0
	mov cx, 8
s:
	mov ax, a
	mov es, ax
	mov ax, es:[bx]
	mov ds:[bx], ax
	
	mov ax, b
	mov es, ax
	mov ax, es:[bx]
	add ds:[bx], ax

	inc bx
	loop s

	mov ax, 4c00h
	int 21h

code ends

end start
