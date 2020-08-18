#ifndef INCLUDED_FRAMEBUFFER_H_
#define INCLUDED_FRAMEBUFFER_H_

#include <stddef.h>
#include <stdint.h>

namespace framebuffer
{

enum class vga_color : uint8_t
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    Light_Gray = 7,
    Light_Grey = Light_Gray,
    Dark_Gray = 8,
    Dark_Grey = Dark_Gray,
    Light_Blue = 9,
    Light_Green = 10,
    Light_Cyan = 11,
    Light_Red = 12,
    Light_Magenta = 13,
    Yellow = 14,
    White = 15
};

/* write_cell: writes a character with specified foreground and background color to cell (row, column)
 * 
 * @param row Zero based row index of cell to write
 * @param column Zero based column index of cell to write
 * @param c The character to write into the buffer
 * @param fg Foreground color, specified as a vga_color
 * @param bg Background color, specified as a vga_color
 */
void write_cell(size_t row, size_t column, unsigned char output, vga_color fgColor, vga_color bgColor);

/* move_cursor: moves cursor to cell (row, column). Cursor will be rendered with foreground color on black background.
 * 
 * @param row Zero based row index of new cursor location
 * @param column Zero based column index of new cursor location
 * @param fgColor Foreground color, specified as a framebuffer_color_t
 */
void move_cursor(size_t row, size_t column, vga_color fgColor);

/*
 * clear: clears framebuffer memory
 */
void clear();

/*
 * write: writes a null terminated C style string to the framebuffer with specified foreground and background color
 * 
 * @param string Buffer of characters to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 */
void write(const char* string, vga_color fgColor, vga_color bgColor);

}

#endif // INCLUDED_FRAMEBUFFER_H_
