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

class Context : public IContext
{

public:
    // TODO: cleanup needed
    Context(bsp::Board& board, display::Display& lcd)
        : board_(board), display(lcd), forcedLight_(false)
    {
    }
    bsp::Board& board_;
    display::Display& display;
    timer::Manager<10, 10> timerManager;

    timer::TimerId saveTimer;
    std::array<float, NUMBER_OF_TERMOMETERS> temperatures_;
    hal::memory::Eeprom eeprom;
    void load() override
    {
        // settings = eeprom.template read<Settings>(0x00);
    }

    void store() override
    {
        // eeprom.write(0x0, settings);
    }

    gsl::span<settings::LightChannel> getAllChannels() override
    {
        return gsl::span<settings::LightChannel>{reinterpret_cast<settings::LightChannel*>(&channels_), NUMBER_OF_PWM_CHANNELS + 1};
    }

    gsl::span<const settings::LightChannel> getAllChannels() const override
    {
        return gsl::span<const settings::LightChannel>{reinterpret_cast<const settings::LightChannel*>(&channels_), NUMBER_OF_PWM_CHANNELS + 1};
    }

    const settings::LightChannel& masterChannel() const override
    {
        return channels_.master_;
    }

    settings::LightChannel& masterChannel() override
    {
        return channels_.master_;
    }

    bool forcedLight() const
    {
        return forcedLight_;
    }

    void forcedLight(bool forced)
    {
        forcedLight_ = forced;
    }

private:
    struct Channels
    {
        settings::LightChannel master_;
        std::array<settings::LightChannel, NUMBER_OF_PWM_CHANNELS> channels_;
    };

    Channels channels_;
    bool forcedLight_;
};

} // namespace app
