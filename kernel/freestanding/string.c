#include "string.h"

#include <stddef.h>
#include <stdint.h>

int memcmp(const void* lhs, const void* rhs, size_t count)
{
    const uint8_t* left = (uint8_t*)lhs;
    const uint8_t* right = (uint8_t*)rhs;
    while (count-- > 0)
    {
        if (*left > *right)
        {
            return 1;
        }

        if (*left < *right)
        {
            return -1;
        }

        ++left;
        ++right;
    }

    return 0;
}

void* memcpy(void* restrict destination, const void* restrict source, size_t count)
{
    void* const returnValue = destination;

    for (; count > 0; --count)
    {
        *((uint8_t*)destination++) = *((uint8_t*)source++);
    }

    return returnValue;
}

void* memmove(void* destination, const void* source, size_t count)
{
    void* const returnValue = destination;

    for (; count > 0; --count)
    {
        *((uint8_t*)destination++) = *((uint8_t*)source++);
    }

    return returnValue;
}

void* memset(void* destination, int byte, size_t count)
{
    void* const returnValue = destination;

    for (; count > 0; --count)
    {
        *((uint8_t*)destination++) = (uint8_t)byte;
    }

    return returnValue;
}

size_t strlen(const char* str)
{
    const char* onePastNullTerminator = str;
    while (*(onePastNullTerminator++))
    {

    }

    return onePastNullTerminator - str - 1;
}
