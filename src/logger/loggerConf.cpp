#include "logger/loggerConf.hpp"

constexpr uint8_t STDOUT_FILE_DESCRIPTOR = 1;
constexpr uint8_t STDERR_FILE_DESCRIPTOR = 2;

namespace logger
{

LoggerConf::LoggerConf& LoggerConf::get()
{
    static LoggerConf conf;
    return conf;
}

void LoggerConf::setLogToStderr()
{
    fd_ = STDERR_FILE_DESCRIPTOR;
}

void LoggerConf::setLogToStdout()
{
    fd_ = STDOUT_FILE_DESCRIPTOR;
}

uint8_t getFileDescriptior()
{
    return fd_;
}

} // namespace logger
