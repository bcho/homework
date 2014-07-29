sandbox: sandbox.o
	ld -o sandbox sandbox.o

sandbox.o: sandbox.asm
	nasm -f elf64 -g -F stabs sandbox.asm -l sandbox.lst


ngaroo: ngaroo.o
	ld -o ngaroo ngaroo.o

ngaroo.o: ngaroo.asm
	nasm -f elf64 -g -F stabs ngaroo.asm -l ngaroo.lst
