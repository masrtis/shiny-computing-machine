#include "string.h"

#include "stddef.h"
#include "stdint.h"

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

    // offset of two because onePastNullTerminator is pointing to the byte after the null terminator (-1)
    // and do not include null terminator in string length
    return onePastNullTerminator - str - 2;
}
