.PHONY: main

main: helloworld.s


%.s: %.intel.x86.s %.att.x86.s %.intel.i686.s %.att.i686.s
	mkdir -p build
	mv $? build


%.intel.x86.s: %.c
	gcc -S -masm=intel $< -o $@

%.att.x86.s: %.c
	gcc -S $< -o $@

%.intel.i686.s: %.c
	gcc -S -masm=intel -m32 $< -o $@

%.att.i686.s: %.c
	gcc -S -m32 $< -o $@
