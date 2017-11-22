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
        c    = *s;
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

int pow(int base, int index)
{
    int answer = base;
    for (int i = 1; i < index; ++i)
    {
        answer *= base;
    }

    return answer;
}

int writeToBufferAligned(char* buffer, int data, char suffix, u8 size, char prefix)
{
    int i = 0;
    for (int tmp = data == 0 ? 1 : data; tmp < pow(10, size - 1);)
    {
        tmp *= 10;
        buffer[i++] = prefix;
    }
    i += utils::itoa(data, buffer + i);
    buffer[i++] = suffix;
    return i;
}

int formatDate(char* buffer, const u8 bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_mday, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_mon + 1, '/');
    i += writeToBufferAligned(&buffer[i], t->tm_year + 1900, '\0');

    HAL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

int formatTime(char* buffer, const u8 bufferSize, std::tm* t)
{
    int i = 0;

    i += writeToBufferAligned(&buffer[i], t->tm_hour, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_min, ':');
    i += writeToBufferAligned(&buffer[i], t->tm_sec, '\0');
    HAL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
    return i;
}

void formatDateAndTime(char* buffer, const u8 bufferSize, std::tm* t)
{
    int i = 0;
    i += formatDate(buffer + i, bufferSize - i, t);
    buffer[i - 1] = ' ';
    i += formatTime(buffer + i, bufferSize - i, t);
    HAL_ASSERT_MSG(i <= bufferSize, "Buffer overflow");
}
} // namespace utils
