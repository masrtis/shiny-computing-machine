#ifndef INCLUDED_KPRINT_H_
#define INCLUDED_KPRINT_H_

#include "framebuffer.h"

namespace debug_log
{

enum class Severity : uint8_t
{
    Info,
    Warning,
    Error,
    Fatal
};

struct Options
{
public:
    constexpr Options() = default;
    constexpr explicit Options(Severity category)
        : m_severity(category)
    {

    }

    constexpr framebuffer::vga_color get_foreground_color() const
    {
        switch (m_severity)
        {
        case Severity::Info:
            return framebuffer::vga_color::White;
        case Severity::Warning:
            return framebuffer::vga_color::Yellow;
        case Severity::Error:
            return framebuffer::vga_color::Light_Red;
        case Severity::Fatal:
            return framebuffer::vga_color::Light_Magenta;
        }

        return framebuffer::vga_color::Light_Green;
    }

    const Severity m_severity = Severity::Info;
};

template <typename T>
void log_to_display(const Options& configuration, T toPrint)
{
    framebuffer::write(toPrint, configuration.get_foreground_color(), framebuffer::vga_color::Black);
}

template <typename First, typename... T>
void log_to_display(const Options& configuration, First toPrint, T... remainder)
{
    log_to_display(configuration, toPrint);
    log_to_display(configuration, remainder...);
}

} // namespace debug_log

#endif // INCLUDED_KPRINT_H_
