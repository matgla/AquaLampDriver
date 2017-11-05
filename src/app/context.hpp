#pragma once

#include "app/channelSetting.hpp"
#include "drivers/lcd/display.hpp"

namespace app
{

struct Context
{
    Context(bsp::Board& board, drivers::lcd::Display& lcd)
        : channelSetting(board), display(lcd)
    {
    }

    ChannelSetting channelSetting;
    drivers::lcd::Display& display;
};

} // namespace app
