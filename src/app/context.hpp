#pragma once

#include "app/channelSetting.hpp"
#include "app/timeSetting.hpp"
#include "display/display.hpp"
#include "logger/logger.hpp"
#include "timer/manager.hpp"

constexpr std::size_t NUMBER_OF_TERMOMETERS = 2;

namespace app
{

struct Context
{
    Context(bsp::Board& board, display::Display& lcd, logger::Logger& log)
        : channelSetting(board), display(lcd), logger(log)
    {
    }

    ChannelSetting channelSetting;
    display::Display& display;
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
    std::array<float, NUMBER_OF_TERMOMETERS> temperatures_;
};

} // namespace app
