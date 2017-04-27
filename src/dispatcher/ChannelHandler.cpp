#include "dispatcher/ChannelHandler.hpp"

#include <cstring>

namespace handler
{
ChannelHandler::ChannelHandler(char *name)
: HandlerBase(name)
{}

bool ChannelHandler::accept(char *cmd, char *arg)
{
    return strcmp(cmd, "CH") == 0;
}

void ChannelHandler::handle(char *cmd, char *arg)
{
    // TODO: handle
}


} // namespace handler