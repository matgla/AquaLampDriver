#pragma once

#include "app/channelSetting.hpp"
#include "app/timeSetting.hpp"
#include "drivers/lcd/display.hpp"
#include "logger/logger.hpp"
#include "timer/manager.hpp"

namespace app
{

struct Context
{
    Context(bsp::Board& board, drivers::lcd::Display& lcd, logger::Logger& log)
        : channelSetting(board), display(lcd), logger(log)
    {
    }

    ChannelSetting channelSetting;
    drivers::lcd::Display& display;
    timer::Manager<5, 5> timerManager;
    TimeSetting timeSetting;
    TimeSetting sunshine;
    TimeSetting sunrise;
    logger::Logger& logger;
    
    enum class TimeSettingOptions : char
    {
        SetTime,
        SetSunshine,
        SetSunrise
    };
    TimeSettingOptions timeSettingOption;
};

} // namespace app
