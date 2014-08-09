.PHONY: all clean

all: 1 2


clean: 1 2
	rm -rf $?


%: %.o
	ld -o $@ $<

%.o: %.asm
	nasm -f elf64 -g -F stabs $<
