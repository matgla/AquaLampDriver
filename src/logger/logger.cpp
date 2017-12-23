#include "logger.hpp"

// TODO: Find out how to remove critial section from here
#include "hal/core/criticalSection.hpp"

#include <cassert>

namespace logger
{

Logger::Logger(std::experimental::string_view name, bool insertNewlineWhenDestruct)
    : name_(std::move(name)), insertNewlineWhenDestruct_(insertNewlineWhenDestruct)
{
}

Logger::~Logger()
{
    if (insertNewlineWhenDestruct_)
    {
        operator<<("\n");
    }
    hal::core::stopCriticalSection();
}

void Logger::printHeader(std::experimental::string_view level)
{
    if (!LoggerConf::get().enabled())
    {
        return;
    }

    uint8_t fd = LoggerConf::get().getFileDescriptor();
    hal::core::startCriticalSection();
    write(fd, "<", 1);
    printTimeAndDate();
    write(fd, "> ", 2);

    write(fd, level.data(), strlen(level.data()));
    write(fd, "/", 1);
    write(fd, name_.data(), strlen(name_.data()));
    write(fd, ": ", 2);
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
    if (!LoggerConf::get().enabled())
    {
        return;
    }

    constexpr const int BufferSize = 20;
    char buffer[BufferSize];
    auto t                 = std::time(nullptr);
    struct tm* currentTime = std::localtime(&t);

    utils::formatDateAndTime(buffer, BufferSize, currentTime);
    write(LoggerConf::get().getFileDescriptor(), buffer, strlen(buffer));
}

} // namespace logger
