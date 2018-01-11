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

    const settings::ChannelsSettings& channelsSettings() const
    {
        return channelsSettings_;
    }

    settings::ChannelsSettings& channelsSettings()
    {
        return channelsSettings_;
    }

    u8 currentMasterPower() const
    {
        return powers_.master;
    }

    void currentMasterPower(u8 power)
    {
        powers_.master = power;
    }

    u8& currentMasterPower()
    {
        return powers_.master;
    }

    gsl::span<const u8> currentChannelsPowers() const
    {
        return gsl::span<const u8>{powers_.channels};
    }

    gsl::span<u8> currentChannelsPowers()
    {
        return gsl::span<u8>{powers_.channels};
    }

    gsl::span<u8> allChannelsPowers()
    {
        return gsl::span<u8>{reinterpret_cast<u8*>(&powers_), sizeof(ChannelPowers)};
    }
    
    gsl::span<const u8> allChannelsPowers() const
    {
        return gsl::span<const u8>{reinterpret_cast<const u8*>(&powers_), sizeof(ChannelPowers)};
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
    settings::ChannelsSettings channelsSettings_;
    struct ChannelPowers
    {
        u8 channels[utils::NUMBER_OF_PWM_CHANNELS];
        u8 master;
    };
    ChannelPowers powers_;

    int fastSunriseLength_;
    int fastSunsetLength_;
};

} // namespace app
