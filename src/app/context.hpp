#pragma once

#include <type_traits>

#include "app/settings/channel.hpp"
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
    
struct Context
{
    
    // TODO: cleanup needed
    Context(bsp::Board& board, display::Display& lcd, logger::Logger& log)
        : board_(board), display(lcd), logger(log), forcedLight(false)
    {
    }
    bsp::Board& board_;
    display::Display& display;
    timer::Manager<10, 10> timerManager;

    logger::Logger& logger;
    timer::TimerId saveTimer;
    std::array<float, NUMBER_OF_TERMOMETERS> temperatures_;
    hal::memory::Eeprom eeprom;

    void readSettings()
    {
        // settings = eeprom.template read<Settings>(0x00);
    }

    void saveSettings()
    {
        // eeprom.write(0x0, settings);
    }

    void initSettings()
    {
        // settings.sunrise.hours   = 8;
        // settings.sunrise.minutes = 0;
        // settings.sunrise.seconds = 0;

        // settings.sunshine.hours  = 21;
        // settings.sunrise.minutes = 0;
        // settings.sunrise.seconds = 0;

        // std::memset(settings.channelPowers, 30, sizeof(settings.channelPowers));
        // settings.channelIndex = 0;

        // eeprom.write(0x0, settings);
    }

    bool forcedLight;
    
    gsl::span<settings::Channel> getAllChannels()
    {
        return gsl::span<settings::Channel>{reinterpret_cast<settings::Channel*>(&channels_), sizeof(Channels)};
    }
    
    gsl::span<const settings::Channel> getAllChannels() const
    {
        return gsl::span<const settings::Channel>{reinterpret_cast<const settings::Channel*>(&channels_), sizeof(Channels)};
    }
    
    const settings::Channel& masterChannel() const
    {
        return channels_.master_;
    }
    
    settings::Channel& masterChannel()
    {
        return channels_.master_;
    }
private:
    struct Channels
    {
        std::array<settings::Channel, NUMBER_OF_PWM_CHANNELS> channels_;
        settings::Channel master_;
    };
    
    Channels channels_;
};

} // namespace app
