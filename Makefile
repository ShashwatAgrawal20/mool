CC=gcc
LD=ld

# Set compiler and assembler flags
# -m32: Compile for a 32-bit architecture.
# -ffreestanding: Don't assume a standard library is present.
# -nostdlib: Don't link against the standard C library.
# -fno-builtin: Don't use built-in functions that might rely on a C library.
# -fno-pie: Don't generate position-independent code.
# -O2: Optimization level.
CFLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -fno-pie -O2 -Wall -Wextra

OBJS=boot.o kernel.o

TARGET=mykernel.bin

all: $(TARGET)

$(TARGET): $(OBJS) linker.ld
	$(LD) -m elf_i386 -T linker.ld -o $(TARGET) $(OBJS)

boot.o: boot.s
	$(CC) $(CFLAGS) -c $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean
