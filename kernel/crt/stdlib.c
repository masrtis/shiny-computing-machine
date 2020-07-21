#include "stdlib.h"

#include "stddef.h"
#include "stdint.h"

void* memset(void* destination, int ch, size_t count)
{
    void* const returnValue = destination;

    for (; count > 0; --count)
    {
        *((uint8_t*)destination++) = (uint8_t)ch;
    }

    return returnValue;
}