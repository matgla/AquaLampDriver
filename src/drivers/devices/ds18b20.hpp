#pragma once

#include "bsp/board.hpp"
#include "drivers/interfaces/onewire.hpp"

namespace drivers
{
namespace devices
{

class Ds18b20
{
public:
    Ds18b20(bsp::Board& board);

private:
    interfaces::OneWire<2> bus_;
};

} // namespace devices
} // namespace drivers
