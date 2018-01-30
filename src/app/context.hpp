#pragma once

#include <type_traits>

#include "app/contextInterface.hpp"
#include "app/settings/lightChannel.hpp"
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

class Context : public ContextInterface<Context>
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

    void readSettingsImpl()
    {
        // settings = eeprom.template read<Settings>(0x00);
    }

    void saveSettingsImpl()
    {
        // eeprom.write(0x0, settings);
    }

    void initSettingsImpl()
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

    gsl::span<settings::LightChannel> getAllChannelsImpl()
    {
        return gsl::span<settings::LightChannel>{reinterpret_cast<settings::LightChannel*>(&channels_), NUMBER_OF_PWM_CHANNELS + 1};
    }

    gsl::span<const settings::LightChannel> getAllChannelsImpl() const
    {
        return gsl::span<const settings::LightChannel>{reinterpret_cast<const settings::LightChannel*>(&channels_), NUMBER_OF_PWM_CHANNELS + 1};
    }

    const settings::LightChannel& masterChannelImpl() const
    {
        return channels_.master_;
    }

    settings::LightChannel& masterChannelImpl()
    {
        return channels_.master_;
    }

private:
    struct Channels
    {
        settings::LightChannel master_;
        std::array<settings::LightChannel, NUMBER_OF_PWM_CHANNELS> channels_;
    };

    Channels channels_;
};

} // namespace app
