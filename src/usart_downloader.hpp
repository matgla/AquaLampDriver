#pragma once

#include "usart.hpp"
#include "logger.hpp"

class UsartDownloader
{
public:
    UsartDownloader(Logger& logger);
    void waitForProvider();
    void writeToMemory();
private:
    Logger& logger_;
};