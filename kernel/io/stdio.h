#ifndef INCLUDED_STDIO_H_
#define INCLUDED_STDIO_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*
 *  printf
 * 
 *  @param format Standard printf format string. From cppreference, only format specifiers
 *                '%', 'c', 's', 'd', 'u', and 'p' are supported, with no optional modifiers.
 */

int printf(const char* format, ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // INCLUDED_STDIO_H_
