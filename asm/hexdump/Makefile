.PHONY: all clean

CANDIDATES=1

all: $(CANDIDATES)


clean: $(CANDIDATES)
	rm -rf $?


%: %.o
	ld -o $@ $<

%.o: %.asm
	nasm -f elf64 -g -F stabs $<
