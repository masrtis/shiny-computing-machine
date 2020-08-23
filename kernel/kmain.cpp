#include "framebuffer.h"
#include "logToDisplay.h"

#include "string_test.h"

extern "C" int kmain()
{
    framebuffer::clear();

    debug_log::log_to_display(debug_log::Options(), "This is an info message\n");
    debug_log::log_to_display(debug_log::Options(debug_log::Severity::Warning), "This is a warning message\n");
    debug_log::log_to_display(debug_log::Options(debug_log::Severity::Error), "This is an error message\n");
    debug_log::log_to_display(debug_log::Options(debug_log::Severity::Fatal), "This is a fatal error\n");

    test::run_all_tests();

    debug_log::log_to_display(debug_log::Options(debug_log::Severity::Fatal), "Halted!\n");

    return 0xDEADDEAD;
}
