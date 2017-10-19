#pragma once

#include <string>
#include <type_traits>
#include <vector>

namespace logger
{

class Logger
{
  public:
    Logger(std::string name = "", bool insertNewlineWhenDestruct = false);
    Logger(const Logger&) = default;
    Logger(Logger&&) = default;
    Logger& operator=(const Logger&& other) = delete;
    Logger& operator=(const Logger& other) = delete;
    ~Logger();

    Logger& operator<<(const std::string& data)
    {
        printf("%s", data.c_str());
        return *this;
    }

    Logger debug();
    Logger info();
    Logger warning();
    Logger error();

  protected:
    std::string getFormatedDateAndTime();

    std::string name_;
    bool insertNewlineWhenDestruct_;
};

} // namespace logger
