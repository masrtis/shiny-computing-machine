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

enum class radix : uint8_t
{
    Decimal = 10,
    Hexadecimal = 16
};

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
 * write: writes a single character to the framebuffer with specified foreground and background color
 * 
 * @param output Character to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 */
void write(char output, vga_color fgColor, vga_color bgColor);

/*
 * write: writes a null terminated C style string to the framebuffer with specified foreground and background color
 * 
 * @param output Null terminated buffer of characters to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 */
void write(const char* output, vga_color fgColor, vga_color bgColor);

/*
 * write: writes an integer to the framebuffer with specified foreground and background color
 * 
 * @param output Number to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 */
void write(int output, vga_color fgColor, vga_color bgColor);

/*
 * write: writes a size_t (as base 10) to the framebuffer with specified foreground and background color
 * 
 * @param output Number to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 */
void write(size_t output, vga_color fgColor, vga_color bgColor);

/*
 * write: writes a size_t to the framebuffer with specified foreground and background color
 * 
 * @param output Number to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 * @param base Decimal (10) or Hexadecimal (16) supported
 */
void write(size_t output, vga_color fgColor, vga_color bgColor, radix base);

/*
 * write: writes a pointer valueto the framebuffer with specified foreground and background color
 * 
 * @param output Pointer to write to the screen
 * @param fgColor Foreground color, specified as a vga_color
 * @param bgColor Background color, specified as a vga_color
 */
template <typename T>
void write(const T* output, vga_color fgColor, vga_color bgColor)
{
    static_assert(sizeof(uintptr_t) >= sizeof(output));
    write("0x", fgColor, bgColor);
    write(reinterpret_cast<uintptr_t>(output), fgColor, bgColor);
}

/*
 * render: writes CPU framebuffer memory to VGA memory
 */
void render();

}

#endif // INCLUDED_FRAMEBUFFER_H_
