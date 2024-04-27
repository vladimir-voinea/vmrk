#pragma once

#include <stddef.h>
#include <stdint.h>

class terminal
{
public:
    terminal();
    void write(const char* data);

private:
    void initialize();
    void setcolor(uint8_t color);
    void putentryat(char c, uint8_t color, size_t x, size_t y);
    void putchar(char c);
    void write(const char* data, size_t size);

private:
    size_t terminal_row;
    size_t terminal_column;
    uint8_t terminal_color;
    uint16_t* terminal_buffer;
};