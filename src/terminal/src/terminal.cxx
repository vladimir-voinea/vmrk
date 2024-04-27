#include <terminal.hpp>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

namespace
{

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

}

terminal& terminal::get_instance()
{
    static terminal term;
    return term;
}

terminal::terminal()
{
    initialize();
}
  
void terminal::initialize() 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal::setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal::putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal::scroll(size_t line) {
    unsigned char* video_memory = reinterpret_cast<unsigned char*>(VGA_MEMORY);

    if (line <= 0 || line >= VGA_HEIGHT) {
        return; // No need to scroll if the line count is out of bounds
    }

    // Move rows up by 'line' rows in the VGA buffer
    for (size_t y = 0; y < VGA_HEIGHT - line; ++y) {
        for (size_t x = 0; x < VGA_WIDTH * 2; ++x) {
            size_t src_idx = (y + line) * (VGA_WIDTH * 2) + x;
            size_t dst_idx = y * (VGA_WIDTH * 2) + x;
            video_memory[dst_idx] = video_memory[src_idx];
        }
    }

    // Clear the freed-up lines at the bottom of the screen
    for (size_t y = VGA_HEIGHT - line; y < VGA_HEIGHT; ++y) {
        for (size_t x = 0; x < VGA_WIDTH * 2; ++x) {
            size_t idx = y * (VGA_WIDTH * 2) + x;
            video_memory[idx] = (x % 2 == 0) ? ' ' : 0x07; // Blank space with light-grey color
        }
    }
}

 
void terminal::delete_last_line() {
   volatile unsigned char* ptr;  // Use 'volatile' for hardware mapped memory to prevent optimizations that may skip actual memory write

    for (auto x = 0u; x < VGA_WIDTH * 2; x++) {
        ptr = reinterpret_cast<unsigned char*>(VGA_MEMORY) + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
        *ptr = 0;
    }
}

void terminal::putchar(char c) 
{
    if(c == '\n') {
        terminal_row++;
        terminal_column = 0;
        return;
    }

	unsigned char uc = c;
 
	putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			for(auto line = 1u; line <= VGA_HEIGHT - 1; line++)
			{
				scroll(line);
			}
			delete_last_line();
			terminal_row = VGA_HEIGHT - 1;
		}
	}
}
 
void terminal::write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		putchar(data[i]);
}
 
void terminal::write(const char* data) 
{
	write(data, strlen(data));
}