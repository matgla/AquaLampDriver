#pragma once

#include <array>
#include <boost/sml.hpp>
#include <cstdio>
#include <cstring>

#include "app/contextInterface.hpp"
#include "app/statemachines/appSm.hpp"
#include "bsp/board.hpp"
#include "controller/lightController.hpp"
#include "display/display.hpp"
#include "drivers/devices/ds18b20.hpp"
#include "hal/memory/eeprom.hpp"
#include "logger/logger.hpp"
#include "timer/manager.hpp"

constexpr float TEMPERATURE_TRESHOLD = 28;
constexpr float TEMPERATURE_STEP     = 2;
constexpr float TEMPERATURE_HIST     = 2;


namespace app
{

enum class LightStates
{
    On,
    Off,
    QuickSunrise,
    Sunrise,
    QuickSunshine,
    Sunshine,
    Night
};

class App
{
public:
    App(display::Display& driver, bsp::Board& board, app::IContext& context);

    void run();
    void start();

    enum class State
    {
        Off,
        Show,
        Menu
    };

private:
    void onShow();

    void delayedBacklightOff();


    app::IContext& context_;
    controller::LightController<> lightController_;
    logger::Logger logger_;
    bsp::Board& board_;
    display::Display& display_;
    State state_;
    bool backlight_;
};

} // namespace app
