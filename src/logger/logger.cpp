#include "logger.hpp"

#include <cassert>

namespace logger
{

Logger::Logger(std::experimental::string_view name, bool insertNewlineWhenDestruct)
    : name_(std::move(name)), insertNewlineWhenDestruct_(insertNewlineWhenDestruct), fd_(1)
{
}

Logger::~Logger()
{
    if (insertNewlineWhenDestruct_)
    {
        operator<<("\n");
    }
}

void Logger::printHeader(std::experimental::string_view level)
{
    write(fd_, "<", 1);
    printTimeAndDate();
    write(fd_, "> ", 2);

    write(fd_, level.data(), strlen(level.data()));
    write(fd_, "/", 1);
    write(fd_, name_.data(), strlen(name_.data()));
    write(fd_, ": ", 2);
}

Logger Logger::debug()
{
    printHeader("DBG");
    return Logger(name_, true);
}

Logger Logger::info()
{
    printHeader("INF");
    return Logger(name_, true);
}

Logger Logger::warning()
{
    printHeader("WRN");
    return Logger(name_, true);
}

Logger Logger::error()
{
    printHeader("ERR");
    return Logger(name_, true);
}

int Logger::writeTimePartToBufferWithAlign(char* buffer, int data, char suffix)
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

void Logger::formatTime(char* buffer, const u8 bufferSize, std::tm* t)
{
    u8 i = 0;

    i += writeTimePartToBufferWithAlign(buffer + i, t->tm_mday, '/');
    i += writeTimePartToBufferWithAlign(buffer + i, t->tm_mon + 1, '/');
    i += writeTimePartToBufferWithAlign(buffer + i, t->tm_year + 1900, ' ');
    i += writeTimePartToBufferWithAlign(buffer + i, t->tm_hour, ':');
    i += writeTimePartToBufferWithAlign(buffer + i, t->tm_min, ':');
    i += writeTimePartToBufferWithAlign(buffer + i, t->tm_sec, '\0');

    assert(i < bufferSize);
}

void Logger::printTimeAndDate()
{
    constexpr const int BufferSize = 21;
    char buffer[BufferSize];
    auto t = std::time(nullptr);
    struct tm* currentTime = std::localtime(&t);

    // std::strftime(static_cast<char*>(buffer), BufferSize, "%d/%m/%y %H:%M:%S", currentTime);
    formatTime(buffer, BufferSize, currentTime);
    write(fd_, buffer, strlen(buffer));
}


} // namespace logger
