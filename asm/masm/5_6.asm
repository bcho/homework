assume cs:code

a segment
	dw 1, 2, 3, 4, 5, 6, 7, 8, 9, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh, 0ffh
a ends

b segment
	dw 0, 0, 0, 0, 0, 0, 0, 0
b ends

code segment

start:

	mov ax, b
	mov ds, ax		; 建立结果段空间

	mov ax, a
	mov es, ax		; 建立源数据段空间

	mov bx, 0
	mov cx, 10h
s0:
	push es:[bx]

	inc bx
	loop s0

	mov bx, 0
	mov cx, 10h
s1:
	pop ds:[bx]

	inc bx
	loop s1

	mov ax, 4c00h
	int 21h

code ends

end start
