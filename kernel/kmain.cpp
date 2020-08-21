#include "framebuffer.h"
#include "logToDisplay.h"

#include "string_test.h"

extern "C" int kmain()
{
    framebuffer::clear();

    test::run_all_tests();

    debug_log::log_to_display(debug_log::Options(debug_log::Severity::Fatal), "Halted!\n");

    framebuffer::render();

    return 0xDEADDEAD;
}
