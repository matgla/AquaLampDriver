#include <cstdlib>
#include <cstring>

#include "dispatcher/handlerBase.hpp"

namespace handler
{
HandlerBase::HandlerBase(char *name)
    : name_(reinterpret_cast<char *>(malloc(sizeof(char) * (strlen(name) + 1)))),
      logger_(name)
{
    strcpy(name_.get(), name);
}

char *HandlerBase::getName()
{
    return name_.get();
}
} // namespace handler
