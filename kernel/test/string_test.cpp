#include "string_test.h"

#include "string.h"

#include "logToDisplay.h"

namespace test
{

namespace
{

void memcmp_returns_zero_when_memory_equal()
{
    const char testString[] = "TEST";

    const auto result = memcmp(testString, testString, sizeof(testString));
    if (result == 0)
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Info}, "memcmp_returns_zero_when_memory_equal passed\n");
    }
    else
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Error}, "memcmp_returns_zero_when_memory_equal failed with actual = ", result, '\n');
    }
}

void memcmp_returns_negative_1_when_first_argument_sorts_before_second()
{
    const char first[] = "AAA";
    const char second[] = "AAB";

    const auto result = memcmp(first, second, sizeof(first));
    if (result == -1)
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Info}, "memcmp_returns_negative_1_when_first_argument_sorts_before_second passed\n");
    }
    else
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Error}, "memcmp_returns_negative_1_when_first_argument_sorts_before_second failed with actual = ", result, '\n');
    }
}

void memcmp_returns_postive_1_when_first_argument_sorts_after_second()
{
    const char first[] = "BBB";
    const char second[] = "BBA";

    const auto result = memcmp(first, second, sizeof(first));
    if (result == 1)
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Info}, "memcmp_returns_postive_1_when_first_argument_sorts_after_second passed\n");
    }
    else
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Error}, "memcmp_returns_postive_1_when_first_argument_sorts_after_second failed with actual = ", result, '\n');
    }
}

void strlen_returns_zero_on_empty_string()
{
    const auto length = strlen("");
    if (length == 0)
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Info}, "strlen_returns_zero_on_empty_string passed\n");
    }
    else
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Error}, "strlen_returns_zero_on_empty_string failed with actual = ", length, '\n');
    }
}

void strlen_returns_4_for_test_string()
{
    const auto length = strlen("TEST");
    if (length == 4)
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Info}, "strlen_returns_4_for_test_string passed\n");
    }
    else
    {
        debug_log::log_to_display(debug_log::DisplayOptions{debug_log::Severity::Error}, "strlen_returns_4_for_test_string failed with actual = ", length, '\n');
    }
}

} // namespace

void run_all_tests()
{
    memcmp_returns_zero_when_memory_equal();
    memcmp_returns_negative_1_when_first_argument_sorts_before_second();
    memcmp_returns_postive_1_when_first_argument_sorts_after_second();

    strlen_returns_zero_on_empty_string();
    strlen_returns_4_for_test_string();
}

} // namespace test
