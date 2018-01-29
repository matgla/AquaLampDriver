#include "app/app.hpp"

#include <cmath>

#include "app/statemachines/events.hpp"
#include "bsp/board.hpp"
#include "hal/core/criticalSection.hpp"
#include "hal/time/rtc.hpp"
#include "hal/time/watchdog.hpp"
#include "logger/logger.hpp"


namespace app
{
App::App(display::Display& display, bsp::Board& board)
    : logger_("App"),
      display_(display),
      board_(board),
      context_(board, display, logger_),
      backlight_(false),
      statemachine_(context_),
      termometers_(board),
      lightState_(LightStates::Off)
{
}

void App::applyBrightness()
{
    // board_.ledPwm1.setPulse(context_.temporarySettings.channelPowers[1] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm2.setPulse(context_.temporarySettings.channelPowers[2] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm3.setPulse(context_.temporarySettings.channelPowers[3] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm4.setPulse(context_.temporarySettings.channelPowers[4] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm5.setPulse(context_.temporarySettings.channelPowers[5] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm6.setPulse(context_.temporarySettings.channelPowers[6] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm7.setPulse(context_.temporarySettings.channelPowers[7] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm8.setPulse(context_.temporarySettings.channelPowers[8] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm9.setPulse(context_.temporarySettings.channelPowers[9] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm10.setPulse(context_.temporarySettings.channelPowers[10] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm11.setPulse(context_.temporarySettings.channelPowers[11] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm12.setPulse(context_.temporarySettings.channelPowers[12] * (static_cast<float>(context_.masterPower) / 100));
    // board_.ledPwm13.setPulse(context_.temporarySettings.channelPowers[13] * (static_cast<float>(context_.masterPower) / 100));
}

void App::performSunriseStep(std::time_t now, int sunriseTime)
{
    int masterPower       = context_.settings.channelPowers[0];
    std::time_t timeToEnd = sunriseTime + now;
    // int powerDiff         = masterPower - context_.masterPower;
    int stepBase = std::abs(now);
    if (powerDiff != 0)
    {
        stepBase = std::abs(timeToEnd / powerDiff);
    }
    bool increase = powerDiff > 0 ? true : false;
    // int step      = stepBase + context_.masterPower * stepBase;
    logger_.info() << "masterPower: " << masterPower << ", timeToEnd: " << timeToEnd << ", powerDiff: " << powerDiff << ", stepBase: " << stepBase
                   << ", increase: " << increase << ", step: " << step;
    if (step + now < 0)
    {
        if (increase)
        {

            // context_.masterPower += 1;
            // logger_.info() << "current power: " << context_.masterPower;
        }
        else
        {
            // context_.masterPower -= 1;
            // logger_.info() << "current power: " << context_.masterPower;
        }

        applyBrightness();
    }
}


void App::processLight(std::time_t time)
{
    switch (lightState_)
    {
        case LightStates::On:
        {
            logger_.info() << "On: " << time;
            if (!isLightTime() && getTimeToSunshine(time) <= 1000) // 1000 = time when decide that we have startup system, and rise should be quick
            {
                lightState_ = LightStates::Sunshine;
                lightSteps_ = 0;
            }
            else if (!isLightTime() && getTimeToSunshine(time) > 1000)
            {
                lightState_ = LightStates::QuickSunshine;
                lightSteps_ = 0;
            }
        }
        break;
        case LightStates::Off:
        {
            logger_.info() << "Off: " << time;

            if (isLightTime() && getTimeToSunrise(time) <= 1000) // 1000 = time when decide that we have startup system, and rise should be quick
            {
                lightState_ = LightStates::Sunrise;
                lightSteps_ = 0;
            }
            else if (isLightTime() && getTimeToSunrise(time) > 1000)
            {
                lightState_ = LightStates::QuickSunrise;
                lightSteps_ = 0;
            }
        }
        break;
        case LightStates::QuickSunrise:
        {
            logger_.info() << "QuickSunrise: " << time;

            int offset = 0;
            // if (quickSunriseTime_ - time < context_.settings.channelPowers[0] - context_.masterPower)
            {
                // offset = context_.settings.channelPowers[0] - context_.masterPower - (quickSunriseTime_ - time);
            }
            if (time < quickSunriseTime_ + offset)
            {
                performSunriseStep(time, getTimeToSunrise(time));
            }
            else
            {
                lightState_ = LightStates::On;
            }
        }
        break;
        case LightStates::Sunrise:
        {
            logger_.info() << "Sunrise: " << time;

            int offset = 0;
            // if (getTimeToSunrise(time) + sunriseTime_ < context_.settings.channelPowers[0] - context_.masterPower)
            {
                // offset = context_.settings.channelPowers[0] - context_.masterPower - (sunriseTime_ - time);
            }
            logger_.info() << "Offset: " << offset;

            if (getTimeToSunrise(time) < sunriseTime_ + offset)
            {
                performSunriseStep(-1 * getTimeToSunrise(time), sunriseTime_ + offset);
            }
            else
            {
                lightState_ = LightStates::On;
            }
        }
        break;
        case LightStates::QuickSunshine:
        {
            logger_.info() << "Quick Sunshine: " << time;

            int offset = 0;
            // if (quickSunshineTime_ - time < context_.settings.channelPowers[0] - context_.masterPower)
            {
                // offset = context_.settings.channelPowers[0] - context_.masterPower - (quickSunshineTime_ - time);
            }
            if (time < quickSunshineTime_ + offset)
            {
                performSunriseStep(time, getTimeToSunshine(time));
            }
            else
            {
                lightState_ = LightStates::Off;
            }
        }
        break;
        case LightStates::Sunshine:
        {
            logger_.info() << "Sunshine: " << time;

            int offset = 0;
            // if (getTimeToSunshine(time) + sunshineTime_ < std::abs(context_.masterPower - context_.settings.channelPowers[0]))
            {
                // offset = context_.settings.channelPowers[0] - context_.masterPower - (sunshineTime_ - time);
            }
            logger_.info() << "Offset: " << offset;

            if (getTimeToSunshine(time) < sunshineTime_ + offset)
            {
                performSunriseStep(-1 * getTimeToSunshine(time), sunshineTime_ + offset);
            }
            else
            {
                lightState_ = LightStates::Off;
            }
        }
        break;
        case LightStates::Night:
        {
            if (isLightTime())
            {
                lightState_ = LightStates::Sunrise;
                lightSteps_ = 0;
            }
        }
        break;
    }
}

void App::start()
{
    if (hal::core::BackupRegisters::get().isFirstStartup())
    {
        logger_.info() << "Settings initializing";
        // context_.initSettings();
    }

    delayedBacklightOff();
    display_.clear(display::Colors::OFF);
    logger_.info() << "Startup";

    hal::time::Rtc::get().setSecondsHandler([this] {
        this->update();
    });

    board_.led.on();
    board_.registers.startupDone();

    hal::time::WatchDog::enable(2000); // 2s

    logger_.info() << "Started";

    // context_.readSettings();
    // context_.temporarySettings = context_.settings;
    // if (!isLightTime())
    // {
    //     context_.masterPower = 0;
    // }
    applyBrightness();
}

time_t App::getTimeToSunrise(std::time_t now)
{
    struct tm sunriseTime = *std::localtime(&now);
    struct tm nowt        = *std::localtime(&now);

    // sunriseTime.tm_hour = context_.settings.sunrise.hours;
    // sunriseTime.tm_min  = context_.settings.sunrise.minutes;
    // sunriseTime.tm_sec  = context_.settings.sunrise.seconds;

    // clang-format off
        logger_.info() << "Now: " << nowt.tm_hour << ":" << nowt.tm_min << ":" << nowt.tm_sec 
            << ", sunrise: " << sunriseTime.tm_hour << ":" << sunriseTime.tm_min << ":" << sunriseTime.tm_sec 
            << ", diff1: " << (long)(std::difftime(now, mktime(&sunriseTime)));
    // clang-format on
    return std::difftime(now, mktime(&sunriseTime));
}

time_t App::getTimeToSunshine(std::time_t now)
{
    struct tm sunshineTime = *std::localtime(&now);
    struct tm nowt         = *std::localtime(&now);
    // sunshineTime.tm_hour   = context_.settings.sunshine.hours;
    // sunshineTime.tm_min    = context_.settings.sunshine.minutes;
    // sunshineTime.tm_sec    = context_.settings.sunshine.seconds;
    // // clang-format off
    logger_.info() << "Now: " << nowt.tm_hour << ":" << nowt.tm_min << ":" << nowt.tm_sec
                   << ", sunshine: " << sunshineTime.tm_hour << ":" << sunshineTime.tm_min << ":" << sunshineTime.tm_sec
                   << ", diff2: " << (long)(std::difftime(now, mktime(&sunshineTime)));
    // clang-format on

    return std::difftime(now, mktime(&sunshineTime));
}

bool App::isLightTime()
{
    time_t now = std::time(nullptr);

    if (getTimeToSunrise(now) >= 0 && getTimeToSunshine(now) < 0)
    {
        return true;
    }

    return false;
}

void App::update()
{
    time_t now = std::time(nullptr);
    processLight(now);

    hal::core::startCriticalSection();
    statemachine_.process_event(statemachines::events::Update{});
    hal::core::stopCriticalSection();
}

void App::delayedBacklightOff()
{
    if (backlight_ == false)
    {
        display_.backlightOn();
        backlightTimer_ = context_.timerManager.setTimeout(10000, [this] {
            display_.backlightOff();
            logger_.info() << "Backlight off";
            backlight_ = false;
        });
        backlight_      = true;
    }
    else
    {
        auto* timer = context_.timerManager.getTimeoutTimer(backlightTimer_);
        if (timer)
        {
            timer->restart(10000);
        }
    }
}


void App::run()
{
    using namespace statemachines;
    context_.timerManager.setInterval(1000, [this]() {
        termometers_.measureTemperature();
        // context_.temperatures_[0] = termometers_.readTemperature(0);
        // context_.temperatures_[1] = termometers_.readTemperature(1);
    });

    while (!board_.exit())
    {
        hal::time::WatchDog::feed();
        if (board_.downButton.isPressed())
        {
            delayedBacklightOff();
            logger_.info() << "down";
            statemachine_.process_event(events::ButtonDown{});
        }
        if (board_.upButton.isPressed())
        {
            delayedBacklightOff();
            logger_.info() << "up";
            statemachine_.process_event(events::ButtonUp{});
        }
        if (board_.leftButton.isPressed())
        {
            delayedBacklightOff();
            logger_.info() << "left";

            statemachine_.process_event(events::ButtonLeft{});
        }
        if (board_.rightButton.isPressed())
        {
            delayedBacklightOff();
            logger_.info() << "right";
            statemachine_.process_event(events::ButtonRight{});
        }
        if (board_.selectButton.isPressed())
        {
            delayedBacklightOff();
            logger_.info() << "select";
            statemachine_.process_event(events::ButtonSelect{});
        }
        if (board_.backButton.isPressed())
        {
            delayedBacklightOff();
            logger_.info() << "back";
            statemachine_.process_event(events::ButtonBack{});
        }

        // measure temperature

        processTemperature();

        // make actions
        board_.run();
        context_.timerManager.run();
    }
    hal::time::Rtc::get().stop();
}

void App::processTemperature()
{
    // for (std::size_t i = 0; i < context_.temperatures_.size(); ++i)
    // {
    //     if (context_.temperatures_[i] >= TEMPERATURE_TRESHOLD && (context_.temperatures_[i] - temperaturesHistory_[i]) > TEMPERATURE_HIST)
    //     {
    //         update();
    //         board_.fanPwm1.setPulse(100);
    //         board_.fanPwm2.setPulse(100);
    //         temperaturesHistory_[i] = context_.temperatures_[i];
    //         logger_.info() << "Fan: 100%";
    //     }
    //     else if (context_.temperatures_[i] < TEMPERATURE_TRESHOLD && (context_.temperatures_[i] - temperaturesHistory_[i]) < -1 * TEMPERATURE_HIST)
    //     {
    //         update();
    //         board_.fanPwm1.setPulse(0);
    //         board_.fanPwm2.setPulse(0);
    //         temperaturesHistory_[i] = context_.temperatures_[i];
    //         logger_.info() << "Fan: 0%";
    //     }
    // }
}

} // namespace app
