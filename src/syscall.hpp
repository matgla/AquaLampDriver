#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

extern "C" {

extern int errno;

int _gettimeofday(struct timeval* tv, void* tzvp);


int _close(int file);
int _fstat(int file, struct stat* st);

int _isatty(int file);

int _lseek(int file, int ptr, int dir);

int _open(const char* name, int flags, int mode);
int _read(int file, char* ptr, int len);
int _kill();

int _getpid();

void _exit(int code);
caddr_t _sbrk(int incr);

int _write(int file, const char* ptr, int len);
}