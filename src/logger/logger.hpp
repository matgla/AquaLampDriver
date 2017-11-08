#pragma once

#include <cstdio>
#include <experimental/string_view>
#include <string>
#include <type_traits>
#include <vector>

#include <unistd.h>

#include "utils.hpp"


namespace logger
{

class Logger
{
    constexpr static u8 numberConversionBase = 10;

public:
    Logger(std::experimental::string_view name, bool insertNewlineWhenDestruct = false);
    Logger(const Logger&) = default;
    Logger(Logger&&) = default;
    Logger& operator=(const Logger&& other) = delete;
    Logger& operator=(const Logger& other) = delete;
    ~Logger();

    Logger& operator<<(const std::experimental::string_view& str)
    {
        // printf("%s", data.c_str());
        write(fd_, str.data(), std::strlen(str.data()));
        return *this;
    }

    Logger& operator<<(int data)
    {
        char number[21];
        utils::itoa(data, number, numberConversionBase);
        write(fd_, number, std::strlen(number));
        return *this;
    }

    Logger debug();
    Logger info();
    Logger warning();
    Logger error();

protected:
    void printHeader(std::experimental::string_view level);
    void printTimeAndDate();
    static int writeTimePartToBufferWithAlign(char* buffer, int data, char suffix);
    static void formatTime(char* buffer, const u8 bufferSize, std::tm* t);

    std::experimental::string_view name_;
    bool insertNewlineWhenDestruct_;
    u8 fd_;
};

} // namespace logger
