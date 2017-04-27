#pragma once

namespace handler
{

class IHandler
{
  public:
    virtual ~IHandler() = default;
    virtual void handle(char *cmd, char *arg) = 0;
    virtual bool match(char *cmd, char *arg) = 0;
    virtual char* getName() = 0;
};

using IHandlerPtr = std::unique_ptr<IHandler>;

} // namespace handler