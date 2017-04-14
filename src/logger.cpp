#include "logger.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

#define TIME_BUFFER_SIZE 18

const char* default_name = "default\0";

char buffer[TIME_BUFFER_SIZE];

Logger::Logger()
    : name_(reinterpret_cast<char*>(malloc(sizeof(char) * (strlen(default_name) + 1)))),
      fd_(DEFAULT_FD)
{
    std::memcpy(name_.get(), default_name, strlen(default_name) + 1);
}

Logger::Logger(const char* name, int fd)
    : name_(reinterpret_cast<char*>(malloc(sizeof(char) * (strlen(name) + 1)))),
      fd_(fd)
{
    std::memcpy(name_.get(), name, strlen(name) + 1);
}

const char* Logger::getLevelString(const Level& level)
{
    switch (level)
    {
        case Level::DEBUG:
            return "DBG";
            break;
        case Level::ERROR:
            return "ERR";
            break;
        case Level::INFO:
            return "INF";
            break;
        case Level::TRACE:
            return "TRC";
            break;
        default:
            return "NON";
            break;
    }
}

// Logger::Logger()
// {
//     logLevel = Level::INFO;
//     logOutput = Output::STDOUT;
// }

const char* Logger::getTimeString()
{
    auto t = std::time(nullptr);
    struct tm *currentTime = std::localtime(&t);
    std::strftime(buffer, TIME_BUFFER_SIZE, "%m/%d/%y %H:%M:%S", currentTime);
    return buffer; // TODO: Maybe it is possible to optimize size ?
}

// void logLine(Level level, const char *format, ...)
// {

// }

// void writeToFile(Level level, const char *format, ...)
// {

// }