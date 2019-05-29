CFLAGS = -m64 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
CC = gcc


default: run

.PHONY: default build run clean

multiboot_header.o: multiboot_header.s
	nasm -f elf64 multiboot_header.s

boot.o: boot.s
	nasm -f elf64 boot.s

_io.o: _io.s
	nasm -f elf64 _io.s

kernel.bin: link.ld multiboot_header.o boot.o main.o _io.o io.o
	ld -T link.ld -elf64 multiboot_header.o boot.o main.o _io.o io.o -o kernel.bin

os.iso: kernel.bin grub.cfg
	cp kernel.bin isofiles/boot/
	grub-mkrescue -o os.iso isofiles

build: os.iso

run: os.iso
	qemu-system-x86_64 -machine ubuntu,accel=kvm -m 512 -cdrom os.iso

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

clean:
	rm -f multiboot_header.o
	rm -f boot.o
	rm -f main.o
	rm -f _io.o
	rm -f io.o
	rm -f kernel.bin
	rm -f kernel.elf
	rm -f isofiles/boot/kernel.bin
	rm -f os.iso