#include "logger/loggerConf.hpp"

#include <iostream>

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
    std::cerr << "sterr" << std::endl;
    fileDescriptor_ = STDERR_FILE_DESCRIPTOR;
}

void LoggerConf::setLogToStdout()
{
    std::cerr << "stdcout" << std::endl;

    fileDescriptor_ = STDOUT_FILE_DESCRIPTOR;
}

uint8_t LoggerConf::getFileDescriptor()
{
    return fileDescriptor_;
}

void LoggerConf::setFileDescriptor(uint8_t fd)
{
    fileDescriptor_ = fd;
}

void LoggerConf::enable()
{
    enabled_ = true;
}

void LoggerConf::disable()
{
    enabled_ = false;
}

bool LoggerConf::enabled()
{
    return enabled_;
}

LoggerConf::LoggerConf()
    : fileDescriptor_(STDOUT_FILE_DESCRIPTOR), enabled_(true)
{
}

} // namespace logger
