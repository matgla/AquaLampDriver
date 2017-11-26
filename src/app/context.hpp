#pragma once

#include "app/timeSetting.hpp"
#include "display/display.hpp"
#include "hal/memory/eeprom.hpp"
#include "logger/logger.hpp"
#include "timer/manager.hpp"

constexpr std::size_t NUMBER_OF_TERMOMETERS  = 2;
constexpr std::size_t NUMBER_OF_PWM_CHANNELS = 13;

namespace app
{

struct Settings
{
    TimeSetting sunrise;
    TimeSetting sunshine;
    int channelIndex;
    u8 channelPowers[NUMBER_OF_PWM_CHANNELS + 1]; // with master on 0 position
};


struct Context
{
    Context(bsp::Board& board, display::Display& lcd, logger::Logger& log)
        : board_(board), display(lcd), logger(log), changedPower(false), forcedLight(false)
    {
    }

    bsp::Board& board_;
    display::Display& display;
    timer::Manager<10, 10> timerManager;

    TimeSetting timeSetting;
    logger::Logger& logger;
    timer::TimerId saveTimer;
    bool changedPower;
    enum class TimeSettingOptions : char
    {
        SetTime,
        SetSunshine,
        SetSunrise
    };
    TimeSettingOptions timeSettingOption;
    std::array<float, NUMBER_OF_TERMOMETERS> temperatures_;
    hal::memory::Eeprom eeprom;

    Settings settings;
    Settings temporarySettings;
    u8 masterPower;

    void readSettings()
    {
        settings = eeprom.template read<Settings>(0x00);
    }

    void saveSettings()
    {
        eeprom.write(0x0, settings);
    }

    void initSettings()
    {
        settings.sunrise.hours   = 8;
        settings.sunrise.minutes = 0;
        settings.sunrise.seconds = 0;

        settings.sunshine.hours  = 21;
        settings.sunrise.minutes = 0;
        settings.sunrise.seconds = 0;

        std::memset(settings.channelPowers, 30, sizeof(settings.channelPowers));
        settings.channelIndex = 0;

        eeprom.write(0x0, settings);
    }

    bool forcedLight;
};

} // namespace app
