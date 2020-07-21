#include "framebuffer.h"

int kmain(void)
{
    framebuffer_clear();

    framebuffer_write_cell(0, 0, 'A', FRAMEBUFFER_WHITE, FRAMEBUFFER_GREEN);
    framebuffer_move_cursor(0, 1, FRAMEBUFFER_LIGHT_GRAY);
    return 0xDEADDEAD;
}
