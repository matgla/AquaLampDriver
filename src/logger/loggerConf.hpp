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

    uint8_t getFileDescriptor();
    void setFileDescriptor(uint8_t fd);
    void enable();
    void disable();

    bool enabled();

private:
    LoggerConf();

    uint8_t fileDescriptor_;
    bool enabled_;
};

} // namespace logger
