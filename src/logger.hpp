#pragma once
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <memory>

#include "memoryHelpers.hpp"
#include "utils.hpp"

#define SPACE_SIZE 40

#ifdef BUILD_TESTS
#define DEFAULT_FD 2
#else
#define DEFAULT_FD 0
#endif

enum class Level
{
    DEBUG,
    INFO,
    ERROR,
    TRACE
};

enum class Output
{
    STDOUT,
    FILE,
    NONE
};

class Logger
{
  public:
    Logger();
    Logger(const char *space, int fd = 0);

    // template <typename

    template <typename Type>
    Logger &operator<<(Type text)
    {
        // TODO: Add api for system calls ( all ) with splitted backend
        write(fd_, text, strlen(text));
        return *this;
    }

    Logger &operator<<(u8 ch)
    {
        char text[4];
        utils::itoa(ch, text, 10);
        write(fd_, text, strlen(text));
        return *this;
    }

    Logger &operator<<(u32 ch)
    {
        char text[40];
        utils::itoa(ch, text, 10);
        write(fd_, text, strlen(text));
        return *this;
    }

    Logger &operator<<(char ch)
    {
        char text[1];
        text[0] = ch;
        write(fd_, text, strlen(text));
        return *this;
    }

    Logger &operator<<(int ch)
    {
        char text[20];
        utils::itoa(ch, text, 10);
        write(fd_, text, strlen(text));
        return *this;
    }

    Logger &operator<<(const Level &level)
    {
        write(fd_, "<", 1);
        const char *time = getTimeString();
        write(fd_, time, strlen(time));
        write(fd_, "> ", 2);
        write(fd_, getLevelString(level), strlen(getLevelString(level)));
        write(fd_, "/", 1);
        write(fd_, name_.get(), strlen(name_.get()));
        write(fd_, ": ", 2);
        return *this;
    }

    Logger &info();
    Logger &error();

  private:
    const char *getLevelString(const Level &level);
    const char *getTimeString();
    std::unique_ptr<char, Deleter> name_;
    int fd_;
};