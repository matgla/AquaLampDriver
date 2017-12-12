#pragma once

#include <cstdint>

namespace logger
{

class LoggerConf
{
public:
    static LoggerConf& get();

    void setLogToStderr();
    void setLogToStdout();

    uint8_t getFileDescriptior();

private:
    LoggerConf();

    uint8_t fileDescriptor_;
};

} // namespace logger
