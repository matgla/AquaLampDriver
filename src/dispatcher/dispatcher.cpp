#include "dispatcher.hpp"

#include <cstring>

namespace dispatcher
{
Dispatcher::Dispatcher() : logger_("Handler\0")
{
}

bool Dispatcher::registerHandler(handler::IHandlerPtr handler)
{
    handlers_.push_back(std::move(handler));
}

bool Dispatcher::handle(char *msg)
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

    for (auto& handler : handlers_)
    {
        if (handler->accept(cmd, arg))
        {
            logger_.info() << "Handler " << handler->getName() 
                << " accepted execution";
            handler->handle(cmd, arg);
        }
    }
}


} // namespace handler