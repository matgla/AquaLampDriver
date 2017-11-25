#pragma once

#include <cstdint>

namespace bsp
{

enum class Channels
{
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
    Channel8,
    Channel9,
    Channel10,
    Channel11,
    Channel12,
    Channel13,
    Channel14,
    Channel15,
    Channel16
};

template <Channels Channel>
class Pwm
{
public:
    Pwm();
    void setPulse(uint8_t width);
    uint8_t getPulse()
    {
        return pulse_;
    }

private:
    uint32_t period_;
    uint8_t pulse_;
};

} // namespace bsp
