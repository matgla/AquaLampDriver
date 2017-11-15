#include "syscall.hpp"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "hal/time/rtc.hpp"
#include "usart.hpp"
#include "utils.hpp"

register char* stack_ptr asm("sp");

int _gettimeofday(struct timeval* tv, void* tzvp)
{
    UNUSED(tzvp);
    uint64_t t = 0;
    if (hal::time::Rtc::wasInitialized())
    {
        t = hal::time::Rtc::get().getTime();
    }

    tv->tv_sec = t;                        // convert to seconds
    tv->tv_usec = (t % 1000000000) / 1000; // tv->tv_usec = (t % 1000000000) / 1000; // get remaining microseconds
    return t;                              // return non-zero for error
}

#undef errno
int errno = 0;

int _close(int file)
{
    UNUSED(file);
    return 0;
}

int _fstat(int file, struct stat* st)
{
    UNUSED(file, st);
    return 0;
}

int _isatty(int file)
{
    UNUSED(file);
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    UNUSED(file, ptr, dir);
    return 0;
}

int _open(const char* name, int flags, int mode)
{
    UNUSED(name, flags, mode);
    return -1;
}

int _read(int file, char* ptr, int len)
{
    UNUSED(file, ptr, len);
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
    UNUSED(code);
    while (true)
    {
    }
}

caddr_t _sbrk(int incr)
{
    // extern char _end;           /* Defined by the linker */
    // extern char _Min_Heap_Size; /* Defined by the linker */
    // char* prev_heap_end;

    // if (heap_end == 0)
    // {
    //     heap_end = &_end;
    // }

    // prev_heap_end = heap_end;

    // if (heap_end + incr > &_Min_Heap_Size + _end)
    // {
    //     /* Heap and stack collision */
    //     _write(1, "Heap and stack collision\n", 25);
    //     errno = ENOMEM;
    //     return (caddr_t)0;
    // }

    // heap_end += incr;
    // return (caddr_t)prev_heap_end;
    extern char end asm("end");
    static char* heap_end;
    char* prev_heap_end;

    if (heap_end == 0)
        heap_end = &end;

    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr)
    {
        _write(1, "Heap and stack collision\n", 25);
        abort();
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

int _write(int file, const char* ptr, int len)
{
    UNUSED(file);
    hw::USART<hw::USARTS::USART2_PP1>::getUsart().send(ptr, len);

    return len;
}
