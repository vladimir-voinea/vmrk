#pragma once

#include <stddef.h>
#include <stdint.h>

class terminal
{
public:
    terminal(const terminal&) = delete;
    static terminal& get_instance();

    void write(const char* data, size_t size);
    void write(const char* data);
    void scroll(size_t line);

private:
    terminal();
    void initialize();
    void setcolor(uint8_t color);
    void putentryat(char c, uint8_t color, size_t x, size_t y);
    void delete_last_line();
    void putchar(char c);

private:
    size_t terminal_row = 0;
    size_t terminal_column = 0;
    uint8_t terminal_color = 0;
    uint16_t* terminal_buffer = nullptr;
};