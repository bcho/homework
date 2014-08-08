1: 1.o
	ld -o 1 1.o

1.o: 1.asm
	nasm -f elf64 -g -F stabs 1.asm -l 1.lst
