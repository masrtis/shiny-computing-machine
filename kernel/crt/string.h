#ifndef INCLUDED_STRING_H_
#define INCLUDED_STRING_H_

#include "stddef.h"

void* memcpy(void* restrict destination, const void* restrict source, size_t count);
void* memmove(void* destination, const void* source, size_t count);
void* memset(void* destination, int byte, size_t count);

size_t strlen(const char* str);

#endif // INCLUDED_STRING_H_
