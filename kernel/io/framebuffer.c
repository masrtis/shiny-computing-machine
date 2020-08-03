#include "framebuffer.h"

#include "io.h"

#include "string.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/*
 *  Constants
 */

enum VGA_GEOMETRY
{
    VGA_WIDTH = 80,
    VGA_HEIGHT = 25
};

enum BIT_SIZES
{
    NIBBLE = 4
};

static const size_t BYTES_PER_ROW = VGA_WIDTH * sizeof(uint16_t);

static uint16_t* const framebuffer = (uint16_t*)0x000B8000;

/*
 *  Types
 */

enum framebuffer_bitmasks
{
    COLOR_MASK = 0x0F,
    LOW_BYTE_MASK = 0x000000FF,
    HIGH_BYTE_MASK = 0x0000FF00
};

typedef struct framebuffer_position
{
    size_t row;
    size_t column;
} framebuffer_position;

typedef struct framebuffer_data
{
    uint16_t cells[VGA_WIDTH * VGA_HEIGHT];
    framebuffer_position position;
} framebuffer_data;

/*
 *  Globals
 */

static framebuffer_data framebuffer_cpu = { 0 };

/*
 *  Local functions
 */

static inline size_t framebuffer_get_row_offset(size_t row)
{
    return row * VGA_WIDTH;
}

static inline size_t framebuffer_get_index(size_t row, size_t column)
{
    return framebuffer_get_row_offset(row) + column;
}

static inline uint16_t framebuffer_get_color(uint8_t fgColor, uint8_t bgColor)
{
    return (uint16_t)((fgColor & COLOR_MASK) | ((bgColor & COLOR_MASK) << NIBBLE));
}

static inline uint16_t framebuffer_compute_cell(unsigned char output, uint8_t fgColor, uint8_t bgColor)
{
    return (uint16_t)output | (framebuffer_get_color(fgColor, bgColor) << CHAR_BIT);
}

static inline void framebuffer_position_advance_row(framebuffer_position* position)
{
    ++position->row;
    position->column = 0;
}

static inline size_t framebuffer_position_get_index(const framebuffer_position* position)
{
    return framebuffer_get_index(position->row, position->column);
}

static inline void framebuffer_cpu_advance_row(framebuffer_data* cpuData)
{
    framebuffer_position_advance_row(&cpuData->position);

    if (cpuData->position.row == VGA_HEIGHT)
    {
        memmove(cpuData->cells, cpuData->cells + framebuffer_get_row_offset(1), sizeof(cpuData->cells) - BYTES_PER_ROW);
        memset(cpuData->cells + framebuffer_get_row_offset(VGA_HEIGHT - 1), 0, BYTES_PER_ROW);
        --cpuData->position.row;
    }
}

static inline void framebuffer_cpu_write_to_vga_memory(const framebuffer_data* cpuData)
{
    memcpy(framebuffer, cpuData->cells, sizeof(cpuData->cells));
}

/*
 *  Interface functions
 */

void framebuffer_write_cell(size_t row, size_t column, unsigned char output, uint8_t fgColor, uint8_t bgColor)
{
    framebuffer[framebuffer_get_index(row, column)] = framebuffer_compute_cell(output, fgColor, bgColor);
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
    outb(FRAMEBUFFER_DATA_PORT, (position & HIGH_BYTE_MASK) >> CHAR_BIT);
    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_LOW_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, position & LOW_BYTE_MASK);
}

void framebuffer_clear(void)
{
    memset(framebuffer, 0, sizeof(framebuffer_cpu));
    memset(&framebuffer_cpu, 0, sizeof(framebuffer_cpu));
}

void framebuffer_write(char* string)
{
    framebuffer_write_color(string, FRAMEBUFFER_LIGHT_GRAY, FRAMEBUFFER_BLACK);
}

void framebuffer_write_color(char* string, uint8_t fgColor, uint8_t bgColor)
{
    const size_t len = strlen(string);

    for (size_t i = 0; i <= len; ++i)
    {
        if (string[i] == '\n' || framebuffer_cpu.position.column == VGA_WIDTH)
        {
            framebuffer_cpu_advance_row(&framebuffer_cpu);

            if (string[i] == '\n')
            {
                continue;
            }
        }

        const size_t cellIndex = framebuffer_position_get_index(&framebuffer_cpu.position);
        framebuffer_cpu.cells[cellIndex] = framebuffer_compute_cell(string[i], fgColor, bgColor);

        ++framebuffer_cpu.position.column;
    }

    if (framebuffer_cpu.position.column == VGA_WIDTH)
    {
        framebuffer_cpu_advance_row(&framebuffer_cpu);
    }

    framebuffer_cpu_write_to_vga_memory(&framebuffer_cpu);

    framebuffer_move_cursor(framebuffer_cpu.position.row, framebuffer_cpu.position.column, FRAMEBUFFER_LIGHT_GRAY);
}
