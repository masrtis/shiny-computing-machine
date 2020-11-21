#ifndef INCLUDED_LOG_OPTIONS_H_
#define INCLUDED_LOG_OPTIONS_H_

#include <stdint.h>

namespace debug_log
{

enum class Severity : uint8_t
{
    Info,
    Warning,
    Error,
    Fatal
};

struct LogOptions
{
    constexpr LogOptions() = default;
    constexpr explicit LogOptions(Severity category)
        : m_severity(category)
    {

    }

    const Severity m_severity = Severity::Info;
protected:
    ~LogOptions() = default;
};

}

#endif // INCLUDED_LOG_OPTIONS_H_
