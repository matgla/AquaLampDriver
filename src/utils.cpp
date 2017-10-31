#include "utils.hpp"

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
void itoa(int n, char* s, int base_n)
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
}
}


volatile u64 ticks;

extern "C" {
void SysTick_Handler();
}

void SysTick_Handler()
{
    ticks++;
}


volatile u64 getTicks()
{
    return ticks;
}

void delay(u32 time_ms)
{
    u64 prev = getTicks();
    while (getTicks() < prev + time_ms)
    {
    }
}

void delayS(u32 time)
{
    delay(1000 * time);
}