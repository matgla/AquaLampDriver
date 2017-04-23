#include "handler.hpp"

#include <cstring>

namespace handler
{
Handler::Handler() : logger_("Handler\0")
{
}

bool Handler::handle(char *msg)
{
    logger_.info() << "Handle message: " << msg << "\n";
    char *part;
    part = strtok(msg, " ");
    if (strcmp(part, "CMD") != 0)
    {
        logger_.error() << "Not valid message. 'CMD' should be at first position.\n";
        return false;
    }
    char *cmd;
    cmd = strtok(nullptr, " ");
    logger_.info() << "Got command: " << cmd << "\n";

    int i = 0;
    char *arg = strtok(nullptr, " ");
    while (arg != nullptr)
    {
        logger_.info() << "Get arg " << i << ": " << arg << "\n";
        ++i;
        arg = strtok(nullptr, " ");
    }
}

} // namespace handler