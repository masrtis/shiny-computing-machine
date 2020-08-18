#include "framebuffer.h"

#include "io.h"

#include "string.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

namespace framebuffer
{

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

constexpr size_t get_row_offset(size_t row);
constexpr size_t get_index(size_t row, size_t column);
constexpr uint16_t get_color(vga_color fgColor, vga_color bgColor);
constexpr uint16_t compute_cell(unsigned char output, vga_color fgColor, vga_color bgColor);

/*
 *  Types
 */

class Position
{
public:
    void move_cursor() const
    {
        framebuffer::move_cursor(row, column, vga_color::Light_Gray);
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
        return framebuffer::get_index(row, column);
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
    size_t row = 0;
    size_t column = 0;
};

class Data
{
public:
    constexpr void advance_row()
    {
        position.advance_row();

        if (position.is_ready_to_scroll())
        {
            constexpr size_t BYTES_PER_ROW = VGA_WIDTH * sizeof(uint16_t);

            memmove(cells, cells + get_row_offset(1), FRAMEBUFFER_SIZE_IN_BYTES - BYTES_PER_ROW);
            memset(cells + get_row_offset(VGA_HEIGHT - 1), 0, BYTES_PER_ROW);
            position.scroll();
        }
    }

    constexpr bool is_row_end() const
    {
        return position.is_row_end();
    }

    constexpr void write_cell(char output, vga_color fgColor, vga_color bgColor)
    {
        const size_t cellIndex = position.get_index();
        cells[cellIndex] = compute_cell(output, fgColor, bgColor);
        position.advance_column();
    }

    void clear()
    {
        memset(cells, 0, FRAMEBUFFER_SIZE_IN_BYTES);
        position = Position{};
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
    Position position;
public:
    static constexpr size_t FRAMEBUFFER_SIZE_IN_BYTES = sizeof(cells);
};

/*
 *  Globals
 */

Data cpu_framebuffer;

/*
 *  Local functions
 */

constexpr size_t get_row_offset(size_t row)
{
    return row * VGA_WIDTH;
}

constexpr size_t get_index(size_t row, size_t column)
{
    return get_row_offset(row) + column;
}

constexpr uint16_t get_color(vga_color fgColor, vga_color bgColor)
{
    constexpr size_t NIBBLE = 4;
    constexpr uint8_t COLOR_MASK = 0x0F;
    
    return static_cast<uint16_t>((static_cast<uint8_t>(fgColor) & COLOR_MASK) | ((static_cast<uint8_t>(bgColor) & COLOR_MASK) << NIBBLE));
}

constexpr uint16_t compute_cell(unsigned char output, vga_color fgColor, vga_color bgColor)
{
    return static_cast<uint16_t>(output) | (get_color(fgColor, bgColor) << CHAR_BIT);
}

} // end namespace

/*
 *  Interface functions
 */

void write_cell(size_t row, size_t column, unsigned char output, vga_color fgColor, vga_color bgColor)
{
    framebuffer[get_index(row, column)] = compute_cell(output, fgColor, bgColor);
}

void move_cursor(size_t row, size_t column, vga_color fgColor)
{
    constexpr uint16_t FRAMEBUFFER_COMMAND_PORT = 0x3D4;
    constexpr uint16_t FRAMEBUFFER_DATA_PORT = 0x3D5;

    constexpr uint8_t FRAMEBUFFER_HIGH_BYTE_COMMAND = 14;
    constexpr uint8_t FRAMEBUFFER_LOW_BYTE_COMMAND = 15;

    write_cell(row, column, 0, fgColor, vga_color::Black);

    const auto position = get_index(row, column);

    constexpr uint16_t LOW_BYTE_MASK = 0xFF;
    constexpr uint16_t HIGH_BYTE_MASK = 0xFF00;

    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_HIGH_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, (position & HIGH_BYTE_MASK) >> CHAR_BIT);
    outb(FRAMEBUFFER_COMMAND_PORT, FRAMEBUFFER_LOW_BYTE_COMMAND);
    outb(FRAMEBUFFER_DATA_PORT, position & LOW_BYTE_MASK);
}

void clear()
{
    memset(framebuffer, 0, Data::FRAMEBUFFER_SIZE_IN_BYTES);
    cpu_framebuffer.clear();
}

void write(const char* string, vga_color fgColor, vga_color bgColor)
{
    const auto len = strlen(string);

    for (size_t i = 0; i <= len; ++i)
    {
        if (string[i] == '\n' || cpu_framebuffer.is_row_end())
        {
            cpu_framebuffer.advance_row();

            if (string[i] == '\n')
            {
                continue;
            }
        }

        cpu_framebuffer.write_cell(string[i], fgColor, bgColor);
    }

    if (cpu_framebuffer.is_row_end())
    {
        cpu_framebuffer.advance_row();
    }

    cpu_framebuffer.render();
}

}
