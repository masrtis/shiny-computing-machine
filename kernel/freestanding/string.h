#ifndef INCLUDED_STRING_H_
#define INCLUDED_STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

int memcmp(const void* lhs, const void* rhs, size_t count);
void* memcpy(void* destination, const void* source, size_t count);
void* memmove(void* destination, const void* source, size_t count);
void* memset(void* destination, int byte, size_t count);

size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // INCLUDED_STRING_H_
