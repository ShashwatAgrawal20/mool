#ifndef IDT_H
#define IDT_H

struct idt_entry {
    unsigned short offset0;
    unsigned short selector;
    unsigned short type_attr;
    unsigned short offset1;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned long base;
} __attribute__((packed));

#define _IDT_TYPE_32BIT_INTERRUPT 0x0E
#define _IDT_TYPE_32BIT_TRAP 0x0F
#define _IDT_ATTR_DPL_RING0 0x00
#define _IDT_ATTR_DPL_RING3 0x60
#define _IDT_ATTR_PRESENT 0x80

#define IDT_ENTRY_INIT(offset_, selector_, type_attr_)                         \
    (struct idt_entry) {                                                       \
        .offset0 = (offset_) & 0xFFFF, .offset1 = (offset_ >> 16) & 0xFFFF,    \
        .selector = (selector_) & 0xFFFF, .type_attr = (type_attr_ << 8)       \
    }

#endif // !IDT_H
