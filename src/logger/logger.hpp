#pragma once

#include <experimental/string_view>
#include <string>

#include <unistd.h>

#include "logger/loggerConf.hpp"
#include "utils.hpp"

namespace logger
{

class Logger
{
public:
    Logger(std::experimental::string_view name, bool insertNewlineWhenDestruct = false);
    Logger(const Logger&) = default;
    Logger(Logger&&)      = default;
    Logger& operator=(const Logger&& other) = delete;
    Logger& operator=(const Logger& other) = delete;
    ~Logger();

    Logger& operator<<(const std::experimental::string_view& str)
    {
        if (!LoggerConf::get().enabled())
        {
            return *this;
        }
        write(LoggerConf::get().getFileDescriptor(), str.data(), std::strlen(str.data()));
        return *this;
    }

    Logger& operator<<(int data)
    {
        if (!LoggerConf::get().enabled())
        {
            return *this;
        }
        char number[21];
        utils::itoa(data, number);
        write(LoggerConf::get().getFileDescriptor(), number, std::strlen(number));
        return *this;
    }

    Logger debug();
    Logger info();
    Logger warning();
    Logger error();

protected:
    void printHeader(std::experimental::string_view level);
    void printTimeAndDate();

    std::experimental::string_view name_;
    bool insertNewlineWhenDestruct_;
};

} // namespace logger
