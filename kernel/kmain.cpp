#include "framebuffer.h"
#include "serial.h"

#include "logToDisplay.h"

#include "string_test.h"

extern "C" int kmain()
{
    framebuffer::clear();
    serial::init_com1();

    test::run_all_tests();

    debug_log::log_to_display(debug_log::DisplayOptions(debug_log::Severity::Fatal), "Halted!\n");

    framebuffer::render();

    return 0xDEADDEAD;
}
