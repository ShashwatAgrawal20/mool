#include "gdt.h"
#define _GDT_ENTRIES_NUM 3

struct gdt_entry_struct gdt_entries[_GDT_ENTRIES_NUM];
struct gdt_ptr_struct gdt_ptr;

extern void gdt_flush(unsigned long gdt_ptr_address);

void gdt_init(void) {
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * _GDT_ENTRIES_NUM) - 1;
    gdt_ptr.base = (unsigned long)&gdt_entries;

    // Mandatory NULL segment
    gdt_entries[0] = GDT_ENTRY_INIT(0, 0, 0, 0);

    // 2. The Kernel Code Segment (index 1)
    // Base: 0, Limit: 4GB, Ring 0, 32-bit, 4KiB page granularity.
    unsigned char code_access = _GDT_ACCESS_PRESENT | _GDT_ACCESS_DPL_RING0 |
                                _GDT_ACCESS_S_CODEDATA | _GDT_ACCESS_EXEC |
                                _GDT_ACCESS_RW | _GDT_ACCESS_ACCESSED;
    unsigned char code_gran = _GDT_GRAN_4K_BLOCKS | _GDT_GRAN_32BIT_MODE;
    gdt_entries[1] = GDT_ENTRY_INIT(0, 0xFFFFFFFF, code_access, code_gran);

    // 3. The Kernel Data Segment (index 2)
    // Same as the code segment, but with the Executable bit cleared.
    unsigned char data_access = _GDT_ACCESS_PRESENT | _GDT_ACCESS_DPL_RING0 |
                                _GDT_ACCESS_S_CODEDATA | _GDT_ACCESS_RW |
                                _GDT_ACCESS_ACCESSED;
    unsigned char data_gran = _GDT_GRAN_4K_BLOCKS | _GDT_GRAN_32BIT_MODE;
    gdt_entries[2] = GDT_ENTRY_INIT(0, 0xFFFFFFFF, data_access, data_gran);

    gdt_flush((unsigned long)&gdt_ptr);
}
