#pragma once

#include "utils/types.hpp"

#include <cstring>
#include <stdint.h>
#include <type_traits>


#define UNUSED1(x) (void)(x)

#define UNUSED2(x, y) \
    UNUSED1(x);       \
    UNUSED1(y)

#define UNUSED3(x, y, z) \
    UNUSED2(y, z);       \
    UNUSED1(x)

#define UNUSED4(x, y, z, e) \
    UNUSED3(y, z, e);       \
    UNUSED1(x)

#define UNUSED5(x, y, z, e, f) \
    UNUSED4(y, z, e, f);       \
    UNUSED1(x)

#define UNUSED6(x, y, z, e, f, g) \
    UNUSED5(y, z, e, f, g);       \
    UNUSED1(x)

#define UNUSED7(x, y, z, e, f, g, h) \
    UNUSED6(y, z, e, f, g, h);       \
    UNUSED1(x)

#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, N, ...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1)

#define ALL_UNUSED_IMPL_(nargs) UNUSED##nargs
#define ALL_UNUSED_IMPL(nargs) ALL_UNUSED_IMPL_(nargs)
#define UNUSED(...) ALL_UNUSED_IMPL(VA_NUM_ARGS(__VA_ARGS__)) \
\
(__VA_ARGS__)
/*
** reverse string in place 
*/
void reverse(char* s);

char getNumber(int n);

namespace utils
{

template <typename T>
T itoa(T n, char* s, int base_n = 10)
{
    static_assert(std::is_arithmetic<T>::value, "Type provided for serialize isn't arithmetic");
    T i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do
    {                                   /* generate digits in reverse order */
        s[i++] = getNumber(n % base_n); /* get next digit */
    } while ((n /= base_n) > 0);        /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return i;
}

int writeToBufferAligned(char* buffer, int data, char suffix, u8 size = 2, char prefix = '0');
int formatTime(char* buffer, const u8 bufferSize, std::tm* t);
int formatDate(char* buffer, const u8 bufferSize, std::tm* t);
void formatDateAndTime(char* buffer, const u8 bufferSize, std::tm* t);
}
