#include "stdio.h"

#include "framebuffer.h"

#include "string.h"

#include <stdarg.h>
#include <stdint.h>

namespace
{

template <typename UnsignedNumeric>
constexpr int printf_process_format_char_get_number_of_digits(UnsignedNumeric argument, int base)
{
    int total_digits = 1;

    while (argument != 0)
    {
        argument /= base;
        ++total_digits;
    }

    return total_digits;
}

template <typename T>
constexpr int printf_process_format_char_get_number_of_digits(const T* argument)
{
    // print pointers as hex (0x prefix)
    static_assert(sizeof(uintptr_t) >= sizeof(argument));
    constexpr int total_hex_chars = 2;
    return total_hex_chars + printf_process_format_char_get_number_of_digits(reinterpret_cast<uintptr_t>(argument), 16);
}

constexpr int printf_process_format_char_get_number_of_digits(int argument, int base)
{
    int total_written = 0;
    if (argument < 0)
    {
        ++total_written;
        argument = -argument;
    }

    return total_written + printf_process_format_char_get_number_of_digits<unsigned int>(argument, base);
}

int printf_process_format_char(const char* format, va_list arguments)
{
    switch (*format)
    {
    case '%':
    {
        framebuffer::write('%', framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
        return 1;
    }
    case 'c':
    {
        const unsigned char char_argument = (unsigned char)va_arg(arguments, int);
        framebuffer::write(char_argument, framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
        return 1;
    }
    case 's':
    {
        const char* string_argument = va_arg(arguments, const char*);
        framebuffer::write(string_argument, framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
        return strlen(string_argument);
    }
    case 'd':
    {
        int int_argument = va_arg(arguments, int);
        framebuffer::write(int_argument, framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
        return printf_process_format_char_get_number_of_digits(int_argument, 10);
    }
    case 'u':
    {
        const unsigned int unsigned_argument = va_arg(arguments, int);
        framebuffer::write(static_cast<size_t>(unsigned_argument), framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
        return printf_process_format_char_get_number_of_digits(unsigned_argument, 10);
    }
    case 'p':
    {
        const void* pointer_argument = va_arg(arguments, void*);
        framebuffer::write(pointer_argument, framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
        return printf_process_format_char_get_number_of_digits(pointer_argument);
    }
    }

    // [HALT] undefined, skip for now
    return 0;
}

}

int printf(const char* format, ...)
{
    va_list arguments;
    va_start(arguments, format);

    int total_printed = 0;

    while (*format != '\0')
    {
        if (*format == '%')
        {
            ++format;
            total_printed += printf_process_format_char(format, arguments);
        }
        else
        {
            framebuffer::write(*format, framebuffer::vga_color::Light_Gray, framebuffer::vga_color::Black);
            ++total_printed;
        }

        ++format;
    }

    va_end(arguments);

    return total_printed;
}
