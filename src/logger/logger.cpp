#include "logger.hpp"

#include <mutex>

#include "stdstub.hpp"

namespace logger
{

static std::mutex logMutex;

Logger::Logger(std::string name, bool insertNewlineWhenDestruct)
    : name_(std::move(name)), insertNewlineWhenDestruct_(insertNewlineWhenDestruct)
{
}

Logger::~Logger()
{
    if (insertNewlineWhenDestruct_)
    {
        operator<<("\n");
        logMutex.unlock();
    }
}

Logger Logger::debug()
{
    logMutex.lock();
    printf("<%s> DBG/%s:", getFormatedDateAndTime().c_str(), name_.c_str());
    return Logger(name_, true);
}

Logger Logger::info()
{
    logMutex.lock();
    printf("<%s> INF/%s:", getFormatedDateAndTime().c_str(), name_.c_str());

    return Logger(name_, true);
}

Logger Logger::warning()
{
    logMutex.lock();
    printf("<%s> WRN/%s:", getFormatedDateAndTime().c_str(), name_.c_str());

    return Logger(name_, true);
}

Logger Logger::error()
{
    logMutex.lock();
    printf("<%s> ERR/%s:", getFormatedDateAndTime().c_str(), name_.c_str());

    return Logger(name_, true);
}

std::string Logger::getFormatedDateAndTime()
{
    const int TIME_BUFFER_SIZE = 18;
    char buffer[TIME_BUFFER_SIZE];
    auto t = std::time(nullptr);
    struct tm* currentTime = std::localtime(&t);
    std::strftime(static_cast<char*>(buffer), TIME_BUFFER_SIZE, "%d/%m/%y %H:%M:%S", currentTime);
    return std::string(static_cast<char*>(buffer));
}


} // namespace logger
