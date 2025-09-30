CC=gcc
LD=ld
NASM=nasm

CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -fno-pie -Wall -Wextra -O2
NASMFLAGS=-f elf32

OBJS=boot.o kernel.o gdt.o gdts.o
TARGET=mykernel.bin

all: $(TARGET)

$(TARGET): $(OBJS) linker.ld
	$(LD) -m elf_i386 -T linker.ld -o $(TARGET) $(OBJS)

%.o: %.nasm
	$(NASM) $(NASMFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

debug: $(TARGET)
	qemu-system-i386 -kernel $(TARGET) -S -s

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean
