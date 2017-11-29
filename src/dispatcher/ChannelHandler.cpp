#include "dispatcher/ChannelHandler.hpp"

#include <cstring>

namespace handler
{
ChannelHandler::ChannelHandler(char* name, pwm::ChannelsGroup& channelsGroup)
    : HandlerBase(name),
      channelsGroup_(channelsGroup)
{
}

bool ChannelHandler::accept(char* cmd, char* arg)
{
    return strcmp(cmd, "CH") == 0;
}

void ChannelHandler::handle(char* cmd, char* arg)
{
    char* command = strtok(arg, " ");
    if (!command)
    {
        logger_.error() << "Didn't receive command\n";
        return;
    }

    logger_.info() << "Command " << cmd << " with arg: " << command << "\n";

    arg = strtok(nullptr, " ");
    if (!arg)
    {
        logger_.error() << "Didn't receive parameter\n";
        return;
    }

    while (arg != nullptr)
    {
        char* value;
        value = strtok(nullptr, " ");
        if (!value)
        {
            logger_.error() << "Didn't receive value for: " << arg << "\n";
        }

        int chNr = atoi(arg);
        int val  = atoi(value);
        logger_.info() << "Channel" << chNr << " will be set to: " << val << "\n";

        if (strcmp(command, "SET") == 0)
        {
            channelsGroup_.setChannelPulse(chNr, val);
        }

        arg = strtok(nullptr, " ");
    }
}

} // namespace handler
