#include "framebuffer.h"

#include "io.h"

#include "string.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

namespace
{

/*
 *  Constants
 */

constexpr size_t VGA_WIDTH = 80;
constexpr size_t VGA_HEIGHT = 25;

uint16_t* const framebuffer = reinterpret_cast<uint16_t*>(0x000B8000);

/*
 *  Prototypes
 */

constexpr size_t framebuffer_get_row_offset(size_t row);
constexpr size_t framebuffer_get_index(size_t row, size_t column);
constexpr uint16_t framebuffer_get_color(uint8_t fgColor, uint8_t bgColor);
constexpr uint16_t framebuffer_compute_cell(unsigned char output, uint8_t fgColor, uint8_t bgColor);

/*
 *  Types
 */

class framebuffer_position
{
public:
    void move_cursor() const
    {
        framebuffer_move_cursor(row, column, FRAMEBUFFER_LIGHT_GRAY);
    }

    constexpr void advance_row()
    {
        ++row;
        column = 0;
    }

    constexpr void advance_column()
    {
        ++column;
    }

    constexpr void scroll()
    {
        --row;
    }

    constexpr auto get_index() const
    {
        return framebuffer_get_index(row, column);
    }

    constexpr bool is_row_end() const
    {
        return column == VGA_WIDTH;
    }

    constexpr bool is_ready_to_scroll() const
    {
        return row == VGA_HEIGHT;
    }
private:
    size_t row{0};
    size_t column{0};
};

class framebuffer_data
{
public:
    constexpr void advance_row()
    {
        position.advance_row();

        if (position.is_ready_to_scroll())
        {
            constexpr size_t BYTES_PER_ROW = VGA_WIDTH * sizeof(uint16_t);

            memmove(cells, cells + framebuffer_get_row_offset(1), FRAMEBUFFER_SIZE_IN_BYTES - BYTES_PER_ROW);
            memset(cells + framebuffer_get_row_offset(VGA_HEIGHT - 1), 0, BYTES_PER_ROW);
            position.scroll();
        }
    }

    constexpr bool is_row_end() const
    {
        return position.is_row_end();
    }

    constexpr void write_cell(char output, uint8_t fgColor, uint8_t bgColor)
    {
        const size_t cellIndex = position.get_index();
        cells[cellIndex] = framebuffer_compute_cell(output, fgColor, bgColor);
        position.advance_column();
    }

    void clear()
    {
        memset(cells, 0, FRAMEBUFFER_SIZE_IN_BYTES);
        position = framebuffer_position{};
    }

    void render() const
    {
        write_to_vga_memory();
        position.move_cursor();
    }
private:
    void write_to_vga_memory() const
    {
        memcpy(framebuffer, cells, FRAMEBUFFER_SIZE_IN_BYTES);
    }

    uint16_t cells[VGA_WIDTH * VGA_HEIGHT]{ 0 };
    framebuffer_position position;
public:
    static constexpr size_t FRAMEBUFFER_SIZE_IN_BYTES = sizeof(cells);
};

/*
 *  Globals
 */

framebuffer_data framebuffer_cpu;

/*
 *  Local functions
 */

constexpr size_t framebuffer_get_row_offset(size_t row)
{
    return row * VGA_WIDTH;
}

constexpr size_t framebuffer_get_index(size_t row, size_t column)
{
    return framebuffer_get_row_offset(row) + column;
}

constexpr uint16_t framebuffer_get_color(uint8_t fgColor, uint8_t bgColor)
{
    constexpr size_t NIBBLE = 4;
    constexpr uint8_t COLOR_MASK = 0x0F;
    
    return static_cast<uint16_t>((fgColor & COLOR_MASK) | ((bgColor & COLOR_MASK) << NIBBLE));
}

constexpr uint16_t framebuffer_compute_cell(unsigned char output, uint8_t fgColor, uint8_t bgColor)
{
    return static_cast<uint16_t>(output) | (framebuffer_get_color(fgColor, bgColor) << CHAR_BIT);
}

} // end namespace

/*
 *  Interface functions
 */

void framebuffer_write_cell(size_t row, size_t column, unsigned char output, uint8_t fgColor, uint8_t bgColor)
{
    framebuffer[framebuffer_get_index(row, column)] = framebuffer_compute_cell(output, fgColor, bgColor);
}

void framebuffer_move_cursor(size_t row, size_t column, uint8_t fgColor)
{
    constexpr uint16_t FRAMEBUFFER_COMMAND_PORT = 0x3D4;
    constexpr uint16_t FRAMEBUFFER_DATA_PORT = 0x3D5;

    constexpr uint8_t FRAMEBUFFER_HIGH_BYTE_COMMAND = 14;
    constexpr uint8_t FRAMEBUFFER_LOW_BYTE_COMMAND = 15;

    framebuffer_write_cell(row, column, 0, fgColor, FRAMEBUFFER_BLACK);

    const auto position = framebuffer_get_index(row, column);

    constexpr uint16_t LOW_BYTE_MASK = 0xFF;
    constexpr uint16_t HIGH_BYTE_MASK = 0xFF00;

    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_HIGH_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, (position & HIGH_BYTE_MASK) >> CHAR_BIT);
    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_LOW_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, position & LOW_BYTE_MASK);
}

void framebuffer_clear()
{
    memset(framebuffer, 0, framebuffer_data::FRAMEBUFFER_SIZE_IN_BYTES);
    framebuffer_cpu.clear();
}

void framebuffer_write(const char* string)
{
    framebuffer_write_color(string, FRAMEBUFFER_LIGHT_GRAY, FRAMEBUFFER_BLACK);
}

void framebuffer_write_color(const char* string, uint8_t fgColor, uint8_t bgColor)
{
    const auto len = strlen(string);

    for (size_t i = 0; i <= len; ++i)
    {
        if (string[i] == '\n' || framebuffer_cpu.is_row_end())
        {
            framebuffer_cpu.advance_row();

            if (string[i] == '\n')
            {
                continue;
            }
        }

        framebuffer_cpu.write_cell(string[i], fgColor, bgColor);
    }

    if (framebuffer_cpu.is_row_end())
    {
        framebuffer_cpu.advance_row();
    }

    framebuffer_cpu.render();
}
