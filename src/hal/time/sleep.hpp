#pragma once

#include "utils/types.hpp"

namespace hal
{
namespace time
{

void sleep(u32 seconds);
void msleep(u64 milliseconds);

} // namespace time
} // namespace hal