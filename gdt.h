#ifndef GDT_H
#define GDT_H

struct gdt_entry_struct {
    unsigned short limit0;
    unsigned short base0;
    unsigned char base1;
    unsigned char access;
    unsigned char granularity;
    unsigned char base2;
} __attribute__((packed));

struct gdt_ptr_struct {
    unsigned short limit;
    unsigned long base;
} __attribute__((packed));

#define _GDT_ACCESS_PRESENT 0x80    // (P) Present bit
#define _GDT_ACCESS_DPL_RING0 0x00  // (DPL) Ring 0
#define _GDT_ACCESS_DPL_RING3 0x60  // (DPL) Ring 3
#define _GDT_ACCESS_S_CODEDATA 0x10 // (S) Code/Data segment
#define _GDT_ACCESS_EXEC 0x08       // (E) Executable bit
#define _GDT_ACCESS_DC 0x04         // (DC) Direction/Conforming bit
#define _GDT_ACCESS_RW 0x02         // (RW) Readable(code)/Writable(data)
#define _GDT_ACCESS_ACCESSED 0x01   // (A) Accessed bit. CPU sets it.
#define _GDT_GRAN_4K_BLOCKS 0x80    // (G) Granularity. 1 for 4KiB page.
#define _GDT_GRAN_32BIT_MODE 0x40   // (D/B) size flag. 16&32 bit protected mode
#define _GDT_GRAN_LONG_MODE 0x20    // (L)Long-mode code flag. 1 for 64-bit.

#define GDT_ENTRY_INIT(base, limit, access_byte, gran)                         \
    (struct gdt_entry_struct){.limit0 = (limit) & 0xFFFF,                      \
                              .base0 = (base) & 0xFFFF,                        \
                              .base1 = ((base) >> 16) & 0xFF,                  \
                              .access = (access_byte),                         \
                              .granularity =                                   \
                                  ((gran) & 0xF0) | (((limit) >> 16) & 0x0F),  \
                              .base2 = ((base) >> 24) & 0xFF}

void gdt_init(void);

#endif // !GDT_H
