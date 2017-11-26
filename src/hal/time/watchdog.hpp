#pragma once

namespace hal
{
namespace time
{

class WatchDog
{
public:
    static void enable(int milliseconds);
    static void feed();
};

} // namespace time
} // namespace hal
