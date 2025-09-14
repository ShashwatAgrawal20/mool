#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

volatile unsigned short *const video_memory = (unsigned short *)VIDEO_MEMORY;
const unsigned char DEFAULT_COLOR = 0x70;

unsigned int vga_index = 0;

void clear_screen(void) {
    for (unsigned int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) {
        video_memory[i] = (unsigned short)' ' | (unsigned short)DEFAULT_COLOR
                                                    << 8;
    }
    vga_index = 0;
}

void print_char(const char c) {
    if (c == '\n') {
        unsigned char current_line = vga_index / SCREEN_WIDTH;
        vga_index = (current_line + 1) * SCREEN_WIDTH;
    } else {
        video_memory[vga_index++] =
            (unsigned short)c | (unsigned short)DEFAULT_COLOR << 8;
    }
}

void print_string(const char *str) {
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        print_char(str[i]);
    }
}

void kernel_main(void) {
    clear_screen();

    print_string("  Hello from the Kernel!\n\n");
    print_string("  LFG\n");
}
