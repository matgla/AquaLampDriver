#pragma once

#include <cstdlib>
#include <cstring>

#include "dispatcher/handlerBase.hpp"

namespace handler
{
HandlerBase::HandlerBase(char *name) 
: name_(reinterpret_cast<char *>(malloc(sizeof(char) * (strlen(name) + 1))))
{}

char *HandlerBase::getName()
{
    return name_.get();
}
} // namespace handler
 