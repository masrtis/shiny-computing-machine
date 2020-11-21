#ifndef INCLUDED_LOG_TO_DISPLAY_H_
#define INCLUDED_LOG_TO_DISPLAY_H_

#include "logOptions.h"

#include "framebuffer.h"

namespace debug_log
{

struct DisplayOptions : public LogOptions
{
    constexpr DisplayOptions() = default;
    constexpr explicit DisplayOptions(Severity category)
        : LogOptions(category)
    {

    }

    constexpr framebuffer::vga_color get_foreground_color() const
    {
        switch (m_severity)
        {
        case Severity::Info:
            return framebuffer::vga_color::Light_Green;
        case Severity::Warning:
            return framebuffer::vga_color::Yellow;
        case Severity::Error:
            return framebuffer::vga_color::Light_Red;
        case Severity::Fatal:
            return framebuffer::vga_color::Light_Magenta;
        }

        return framebuffer::vga_color::White;
    }
};

template <typename T>
void log_to_display(const DisplayOptions& configuration, T toPrint)
{
    framebuffer::write(toPrint, configuration.get_foreground_color(), framebuffer::vga_color::Black);
}

template <typename First, typename... T>
void log_to_display(const DisplayOptions& configuration, First toPrint, T... remainder)
{
    log_to_display(configuration, toPrint);
    log_to_display(configuration, remainder...);
}

} // namespace debug_log

#endif // INCLUDED_LOG_TO_DISPLAY_H_
