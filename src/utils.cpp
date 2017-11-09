#include "utils.hpp"

#include <cassert>
#include <cstring>
#include <ctime>

#include "hal/utils/assert.hpp"

/*
** reverse string in place 
*/
void reverse(char* s)
{
    char* j;
    int c;

    j = s + strlen(s) - 1;
    while (s < j)
    {
        c = *s;
        *s++ = *j;
        *j-- = c;
    }
}

char getNumber(int n)
{
    if (n > 9)
    {
        return n - 10 + 'a';
    }
    else
    {
        return n + '0';
    }
}

namespace utils
{
int itoa(int n, char* s, int base_n)
{
    int i, sign;

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

int writeTimePartToBufferWithAlign(char* buffer, int data, char suffix)
{
    int i = 0;
    if (data < 10)
    {
        buffer[i++] = '0';
    }
    i += utils::itoa(data, buffer + i);
    buffer[i++] = suffix;
    return i;
}

int formatTime(char* buffer, const u8 bufferSize, std::tm* t)
{
    int i = 0;

    i += writeTimePartToBufferWithAlign(&buffer[i], t->tm_mday, '/');
    i += writeTimePartToBufferWithAlign(&buffer[i], t->tm_mon + 1, '/');
    i += writeTimePartToBufferWithAlign(&buffer[i], t->tm_year + 1900, '\0');

    HAL_ASSERT_MSG(i < bufferSize, "Buffer overflow");
    return i;
}

int formatDate(char* buffer, const u8 bufferSize, std::tm* t)
{
    int i = 0;

    i += writeTimePartToBufferWithAlign(&buffer[i], t->tm_hour, ':');
    i += writeTimePartToBufferWithAlign(&buffer[i], t->tm_min, ':');
    i += writeTimePartToBufferWithAlign(&buffer[i], t->tm_sec, '\0');
    HAL_ASSERT_MSG(i < bufferSize, "Buffer overflow");
    return i;
}

void formatDateAndTime(char* buffer, const u8 bufferSize, std::tm* t)
{
    int i = 0;
    i += formatDate(buffer + i, bufferSize - i, t);
    buffer[i - 1] = ' ';
    i += formatTime(buffer + i, bufferSize - i, t);
    HAL_ASSERT_MSG(i < bufferSize, "Buffer overflow");
}
} // namespace utils
