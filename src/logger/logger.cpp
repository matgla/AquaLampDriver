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


void Logger::printTimeAndDate()
{
    constexpr const int BufferSize = 22;
    char buffer[BufferSize];
    auto t = std::time(nullptr);
    struct tm* currentTime = std::localtime(&t);

    utils::formatDateAndTime(buffer, BufferSize, currentTime);
    write(fd_, buffer, strlen(buffer));
}

} // namespace logger
