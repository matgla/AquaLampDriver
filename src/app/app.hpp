#pragma once

#include <array>
#include <boost/sml.hpp>
#include <cstdio>
#include <cstring>

#include "app/context.hpp"
#include "app/statemachines/appSm.hpp"
#include "bsp/board.hpp"
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
    App(display::Display& driver, bsp::Board& board);

    void run();
    void start();

private:
    void processLight(std::time_t time);
    void update();
    void processTemperature();
    void delayedBacklightOff();
    bool isLightTime();
    void applyBrightness();
    time_t getTimeToSunrise(std::time_t now);
    time_t getTimeToSunshine(std::time_t now);
    void performSunriseStep(std::time_t now, int sunriseTime);
    logger::Logger logger_;
    display::Display& display_;
    bsp::Board& board_;
    Context context_;
    timer::TimerId backlightTimer_;
    bool backlight_;
    boost::sml::sm<statemachines::AppSm> statemachine_;
    drivers::devices::Ds18b20<NUMBER_OF_TERMOMETERS> termometers_;
    std::array<float, NUMBER_OF_TERMOMETERS> temperaturesHistory_;
    LightStates lightState_;
    int lightSteps_;
    int quickSunriseTime_  = 100;
    int quickSunshineTime_ = 100;
    int sunriseTime_       = 100;
    int sunshineTime_      = 100;
    int pwmStep_           = 0;
};

} // namespace app
