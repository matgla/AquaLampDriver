#pragma once

#include "app/channelSetting.hpp"
#include "drivers/lcd/display.hpp"
#include "timer/manager.hpp"

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
    timer::Manager<5, 5> timerManager;
};

} // namespace app
