#pragma once

#include <cstring>

#include "bsp/board.hpp"
#include "utils/types.hpp"

namespace app
{
struct ChannelSetting
{
    ChannelSetting(bsp::Board& board)
        : board_(board), index(0)
    {
        memset(power, 0, sizeof(power) * sizeof(u8));
    }
    bsp::Board& board_;

    int index;
    u8 power[14];
    u8& masterPower = power[0];
};
} // namespace app
