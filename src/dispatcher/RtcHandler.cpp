#include "dispatcher/RtcHandler.hpp"
#include "rtc/rtc.hpp"

#include <cstring>

namespace handler
{
RtcHandler::RtcHandler(char *name)
    : HandlerBase(name)
{
}

bool RtcHandler::accept(char *cmd, char *arg)
{
    return strcmp(cmd, "RTC") == 0;
}

void RtcHandler::handle(char *cmd, char *arg)
{
    char *command = strtok(arg, " ");
    if (!command)
    {
        logger_.error() << "Didn't receive command\n";
        return;
    }

    logger_.info() << "Command " << cmd << " with arg: " << command << "\n";

    if (strcmp(command, "SET") != 0)
    {
        logger_.error() << "Only SET command is currently supported\n";
        return;
    }

    char *day = strtok(nullptr, " ");
    char *month = strtok(nullptr, " ");
    char *year = strtok(nullptr, " ");
    char *hour = strtok(nullptr, " ");
    char *minute = strtok(nullptr, " ");
    char *second = strtok(nullptr, " ");

    const char *format = "Please set date in format DD MM YYYY HH MM SS\n";

    if (nullptr == day)
    {
        logger_.error() << "Day isn't passed. " << format;
        return;
    }
    if (nullptr == month)
    {
        logger_.error() << "Month isn't passed. " << format;
        return;
    }
    if (nullptr == year)
    {
        logger_.error() << "Year isn't passed. " << format;
        return;
    }
    if (nullptr == hour)
    {
        logger_.error() << "Hour isn't passed. " << format;
        return;
    }
    if (nullptr == minute)
    {
        logger_.error() << "Minute isn't passed. " << format;
        return;
    }
    if (nullptr == second)
    {
        logger_.error() << "Second isn't passed. " << format;
        return;
    }

    rtc::Rtc::setTime(atoi(day), atoi(month), atoi(year), atoi(hour), atoi(minute), atoi(second));
}

} // namespace handler