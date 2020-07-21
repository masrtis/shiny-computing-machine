#include "framebuffer.h"

#include "io.h"

#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"

enum framebuffer_bitmasks
{
    COLOR_MASK = 0x0F,
    LOW_BYTE_MASK = 0x000000FF,
    HIGH_BYTE_MASK = 0x0000FF00
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static uint16_t* const framebuffer = (uint16_t*)0x000B8000;

static inline size_t framebuffer_get_index(size_t row, size_t column)
{
    return row * VGA_WIDTH + column;
}

static inline uint16_t framebuffer_get_color(uint8_t fgColor, uint8_t bgColor)
{
    return (uint16_t)((fgColor & COLOR_MASK) | ((bgColor & COLOR_MASK) << 4));
}

void framebuffer_write_cell(size_t row, size_t column, unsigned char output, uint8_t fgColor, uint8_t bgColor)
{
    framebuffer[framebuffer_get_index(row, column)] = (uint16_t)output | (framebuffer_get_color(fgColor, bgColor) << 8);
}

void framebuffer_move_cursor(size_t row, size_t column, uint8_t fgColor)
{
    enum framebuffer_io_ports
    {
        FRAMEBUFFER_COMMAND_PORT = 0x3D4,
        FRAMEBUFFER_DATA_PORT = 0x3D5
    };

    enum framebuffer_io_commands
    {
        FRAMEBUFFER_HIGH_BYTE_COMMAND = 14,
        FRAMEBUFFER_LOW_BYTE_COMMAND = 15
    };

    framebuffer_write_cell(row, column, 0, fgColor, FRAMEBUFFER_BLACK);

    const size_t position = framebuffer_get_index(row, column);

    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_HIGH_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, (position & HIGH_BYTE_MASK) >> 8);
    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_LOW_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, position & LOW_BYTE_MASK);
}

void framebuffer_clear(void)
{
    memset(framebuffer, 0, VGA_WIDTH * VGA_HEIGHT * sizeof(uint16_t));
}
