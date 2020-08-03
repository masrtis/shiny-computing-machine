#ifndef INCLUDED_FRAMEBUFFER_H_
#define INCLUDED_FRAMEBUFFER_H_

#include <stddef.h>
#include <stdint.h>

typedef enum framebuffer_color
{
    FRAMEBUFFER_BLACK = 0,
    FRAMEBUFFER_BLUE = 1,
    FRAMEBUFFER_GREEN = 2,
    FRAMEBUFFER_CYAN = 3,
    FRAMEBUFFER_RED = 4,
    FRAMEBUFFER_MAGENTA = 5,
    FRAMEBUFFER_BROWN = 6,
    FRAMEBUFFER_LIGHT_GRAY = 7,
    FRAMEBUFFER_LIGHT_GREY = FRAMEBUFFER_LIGHT_GRAY,
    FRAMEBUFFER_DARK_GRAY = 8,
    FRAMEBUFFER_DARK_GREY = FRAMEBUFFER_DARK_GRAY,
    FRAMEBUFFER_LIGHT_BLUE = 9,
    FRAMEBUFFER_LIGHT_GREEN = 10,
    FRAMEBUFFER_LIGHT_CYAN = 11,
    FRAMEBUFFER_LIGHT_RED = 12,
    FRAMEBUFFER_LIGHT_MAGENTA = 13,
    FRAMEBUFFER_LIGHT_BROWN = 14,
    FRAMEBUFFER_WHITE = 15
} framebuffer_color_t;

/* framebuffer_write_cell: writes a character with specified foreground and background color to cell (row, column)
 * 
 * @param row Zero based row index of cell to write
 * @param column Zero based column index of cell to write
 * @param c The character to write into the buffer
 * @param fg Foreground color, specified as a framebuffer_color_t
 * @param bg Background color, specified as a framebuffer_color_t
 */
void framebuffer_write_cell(size_t row, size_t column, unsigned char output, uint8_t fgColor, uint8_t bgColor);

/* framebuffer_move_cursor: moves cursor to cell (row, column). Cursor will be rendered with foreground color on black background.
 * 
 * @param row Zero based row index of new cursor location
 * @param column Zero based column index of new cursor location
 * @param fgColor Foreground color, specified as a framebuffer_color_t
 */
void framebuffer_move_cursor(size_t row, size_t column, uint8_t fgColor);

/*
 * framebuffer_clear: clears framebuffer memory
 */
void framebuffer_clear();

/*
 * framebuffer_write: writes a null terminated C style string to the framebuffer. Foreground color will be light gray, background color black.
 * 
 * @param string Buffer of characters to write to the screen
 */
void framebuffer_write(const char* string);

/*
 * framebuffer_write_color: writes a null terminated C style string to the framebuffer with specified foreground and background color
 * 
 * @param string Buffer of characters to write to the screen
 * @param fgColor Foreground color, specified as a framebuffer_color_t
 * @param bgColor Background color, specified as a framebuffer_color_t
 */
void framebuffer_write_color(const char* string, uint8_t fgColor, uint8_t bgColor);

#endif // INCLUDED_FRAMEBUFFER_H_
