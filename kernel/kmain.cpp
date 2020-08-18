#include "framebuffer.h"

extern "C" int kmain()
{
    framebuffer::clear();

    framebuffer::write_color("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", framebuffer::vga_color::White, framebuffer::vga_color::Green);

    return 0xDEADDEAD;
}
