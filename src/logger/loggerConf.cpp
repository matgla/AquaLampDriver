#include "logger/loggerConf.hpp"

constexpr uint8_t STDOUT_FILE_DESCRIPTOR = 1;
constexpr uint8_t STDERR_FILE_DESCRIPTOR = 2;

namespace logger
{

LoggerConf& LoggerConf::get()
{
    static LoggerConf conf;
    return conf;
}

void LoggerConf::setLogToStderr()
{
    fileDescriptor_ = STDERR_FILE_DESCRIPTOR;
}

void LoggerConf::setLogToStdout()
{
    fileDescriptor_ = STDOUT_FILE_DESCRIPTOR;
}

uint8_t LoggerConf::getFileDescriptior()
{
    return fileDescriptor_;
}

LoggerConf::LoggerConf()
    : fileDescriptor_(STDOUT_FILE_DESCRIPTOR)
{
}

} // namespace logger
