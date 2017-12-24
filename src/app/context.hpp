#pragma once

#include <type_traits>

#include "app/settings/channelsSettings.hpp"
#include "app/settings/timeEventSettings.hpp"
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

    const settings::ChannelsSettings& currentChannelsSettings() const
    {
        return currentChannelsSettings_;
    }

    settings::ChannelsSettings& currentChannelsSettings()
    {
        return currentChannelsSettings_;
    }

    const settings::ChannelsSettings& dayChannelsSettings() const
    {
        return dayChannelsSettings_;
    }

    settings::ChannelsSettings& dayChannelsSettings()
    {
        return dayChannelsSettings_;
    }

    const settings::ChannelsSettings& nightChannelsSettings() const
    {
        return nightChannelsSettings_;
    }

    settings::ChannelsSettings& nightChannelsSettings()
    {
        return nightChannelsSettings_;
    }

    const settings::TimeEventSettings& sunriseSettings() const
    {
        return sunriseSettings_;
    }

    settings::TimeEventSettings& sunriseSettings()
    {
        return sunriseSettings_;
    }

    const settings::TimeEventSettings& sunsetSettings() const
    {
        return sunsetSettings_;
    }

    settings::TimeEventSettings& sunsetSettings()
    {
        return sunsetSettings_;
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

    void fastSunriseLength(u8 length)
    {
        fastSunriseLength_ = length;
    }

    void fastSunsetLength(u8 length)
    {
        fastSunsetLength_ = length;
    }

    int fastSunriseLength()
    {
        return fastSunriseLength_;
    }

    int fastSunsetLength()
    {
        return fastSunsetLength_;
    }

private:
    settings::ChannelsSettings currentChannelsSettings_;
    settings::ChannelsSettings dayChannelsSettings_;
    settings::ChannelsSettings nightChannelsSettings_;

    settings::TimeEventSettings sunriseSettings_;
    settings::TimeEventSettings sunsetSettings_;

    int fastSunriseLength_;
    int fastSunsetLength_;
};

} // namespace app
