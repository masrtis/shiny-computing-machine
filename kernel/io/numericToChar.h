#ifndef INCLUDED_NUMERIC_TO_CHAR_H_
#define INCLUDED_NUMERIC_TO_CHAR_H_

#include <stdint.h>

namespace numeric
{

enum class radix : uint8_t
{
    Decimal = 10,
    Hexadecimal = 16
};

template <typename Numeric>
constexpr auto get_next_digit(Numeric number, Numeric base)
{
    const Numeric onesPlace = number % base;
    const unsigned char digit = onesPlace > 10 ? (onesPlace - 10 + 'A') : (onesPlace + '0');
    return digit;
}

template <typename Numeric>
constexpr void advance_digit(Numeric& number, Numeric base)
{
    number /= base;
}

template <typename Numeric, typename WriteFunction>
constexpr void write_digit(Numeric& number, radix base, WriteFunction writer)
{
    const auto baseAsNumeric = static_cast<Numeric>(base);
    const auto nextDigit = get_next_digit(number, baseAsNumeric);
    advance_digit(number, baseAsNumeric);

    writer(nextDigit);
}

}

#endif // INCLUDED_NUMERIC_TO_CHAR_H_
