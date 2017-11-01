#include "dispatcher.hpp"

#include <cstring>

#include "utils/types.hpp"

namespace dispatcher
{
Dispatcher::Dispatcher()
    : logger_("Handler\0")
{
}

bool Dispatcher::registerHandler(handler::IHandlerPtr handler)
{
    handlers_.push_back(std::move(handler));
}

bool Dispatcher::handle(char* msg)
{
    logger_.info() << "Handle message: " << msg << "\n";
    char* part;
    part = strtok(msg, " ");
    if (strcmp(part, "CMD") != 0)
    {
        logger_.error() << "Not valid message. 'CMD' should be at first position.\n";
        return false;
    }
    char* cmd;
    cmd = strtok(nullptr, " ");
    logger_.info() << "Got command: " << cmd << "\n";

    u8 nrOfSpaces = 2;
    char* args = msg + strlen(part) + strlen(cmd) + nrOfSpaces;
    for (auto& handler : handlers_)
    {
        if (handler->accept(cmd, args))
        {
            logger_.info() << "Handler " << handler->getName()
                           << " accepted execution\n";
            handler->handle(cmd, args);
        }
    }
}

} // namespace handler
