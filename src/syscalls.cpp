#include "stm32includes.hpp"
#include "syscall.hpp"
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>

#include "usart.hpp"
#include "rtc/rtc.hpp"

int _gettimeofday(struct timeval *tv, void *tzvp)
{
    uint64_t t = rtc::Rtc::getTime();

    tv->tv_sec = t;                        // convert to seconds
    tv->tv_usec = (t % 1000000000) / 1000; // tv->tv_usec = (t % 1000000000) / 1000; // get remaining microseconds
    return t;                              // return non-zero for error
}

#undef errno
int errno = 0;

int _close(int file)
{
    return 0;
}

int _fstat(int file, struct stat *st)
{
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

int _read(int file, char *ptr, int len)
{
    return 0;
}

int _kill()
{
    return 0;
}

int _getpid()
{
    return 0;
}

void _exit(int code)
{
}

char *heap_end = 0;
caddr_t _sbrk(int incr)
{
    extern char _heap;  /* Defined by the linker */
    extern char _eheap; /* Defined by the linker */
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_heap;
    }

    prev_heap_end = heap_end;

    if (heap_end + incr > &_eheap)
    {
        /* Heap and stack collision */
        _write(1, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return (caddr_t)0;
    }

    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

int _write(int file, const char *ptr, int len)
{
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().send(ptr, len);

    return len;
}
