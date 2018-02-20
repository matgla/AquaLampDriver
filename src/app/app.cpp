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
      isLightTime_(false),
      isNightTime_(false)
{
}

void App::applyBrightness()
{
    board_.ledPwm1.setPulse(context_.temporarySettings.channelPowers[1] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm2.setPulse(context_.temporarySettings.channelPowers[2] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm3.setPulse(context_.temporarySettings.channelPowers[3] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm4.setPulse(context_.temporarySettings.channelPowers[4] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm5.setPulse(context_.temporarySettings.channelPowers[5] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm6.setPulse(context_.temporarySettings.channelPowers[6] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm7.setPulse(context_.temporarySettings.channelPowers[7] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm8.setPulse(context_.temporarySettings.channelPowers[8] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm9.setPulse(context_.temporarySettings.channelPowers[9] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm10.setPulse(context_.temporarySettings.channelPowers[10] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm11.setPulse(context_.temporarySettings.channelPowers[11] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm12.setPulse(context_.temporarySettings.channelPowers[12] * (static_cast<float>(context_.masterPower) / 100));
    board_.ledPwm13.setPulse(context_.temporarySettings.channelPowers[13] * (static_cast<float>(context_.masterPower) / 100));
}

void App::start()
{
    context_.masterPower = 0;
    applyBrightness();
    if (hal::core::BackupRegisters::get().isFirstStartup())
    {
        logger_.info() << "Settings initializing";
        context_.initSettings();
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

    context_.readSettings();
    context_.temporarySettings = context_.settings;
    if (!isLightTime())
    {
        context_.masterPower = 0;
    }
    applyBrightness();
    board_.fanDriver.setPulse(100);

    context_.settings.sunshine.hours   = 22;
    context_.settings.sunshine.minutes = 30;
    context_.settings.sunshine.seconds = 0;

    context_.settings.sunrise.hours   = 10;
    context_.settings.sunrise.minutes = 30;
    context_.settings.sunrise.seconds = 0;
}

bool App::isLightTime()
{
    time_t now             = std::time(nullptr);
    struct tm sunshineTime = *std::localtime(&now);
    struct tm sunriseTime  = *std::localtime(&now);
    struct tm nowt         = *std::localtime(&now);
    sunshineTime.tm_hour   = context_.settings.sunshine.hours;
    sunshineTime.tm_min    = context_.settings.sunshine.minutes;
    sunshineTime.tm_sec    = context_.settings.sunshine.seconds;

    sunriseTime.tm_hour = context_.settings.sunrise.hours;
    sunriseTime.tm_min  = context_.settings.sunrise.minutes;
    sunriseTime.tm_sec  = context_.settings.sunrise.seconds;

    // clang-format off
        logger_.info() << "Now: " << nowt.tm_hour << ":" << nowt.tm_min << ":" << nowt.tm_sec 
            << ", sunrise: " << sunriseTime.tm_hour << ":" << sunriseTime.tm_min << ":" << sunriseTime.tm_sec 
            << ", sunshine: " << sunshineTime.tm_hour << ":" << sunshineTime.tm_min << ":" << sunshineTime.tm_sec
            << ", diff1: " << (long)(std::difftime(now, mktime(&sunriseTime)))
            << ", diff2: " << (long)(std::difftime(now, mktime(&sunshineTime)));
    // clang-format on
    if (std::difftime(now, mktime(&sunriseTime)) >= 0 && std::difftime(now, mktime(&sunshineTime)) < 0)
    {
        return true;
    }


    return false;
}

void App::update()
{
    if (isLightTime() && !isLightTime_)
    {
        context_.temporarySettings.channelPowers[1]  = 70;
        context_.temporarySettings.channelPowers[2]  = 90;
        context_.temporarySettings.channelPowers[3]  = 70;
        context_.temporarySettings.channelPowers[4]  = 90;
        context_.temporarySettings.channelPowers[5]  = 0;
        context_.temporarySettings.channelPowers[6]  = 70;
        context_.temporarySettings.channelPowers[7]  = 70;
        context_.temporarySettings.channelPowers[8]  = 70;
        context_.temporarySettings.channelPowers[9]  = 90;
        context_.temporarySettings.channelPowers[10] = 70;
        context_.temporarySettings.channelPowers[11] = 90;
        context_.temporarySettings.channelPowers[12] = 70;
        context_.temporarySettings.channelPowers[13] = 90;


        context_.masterPower = 80;


        board_.fanPwm1.setPulse(100);
        board_.fanPwm2.setPulse(100);

        applyBrightness();
        isLightTime_ = true;
        isNightTime_ = false;
    }
    else if (!isLightTime() && !isNightTime_)
    {
        context_.temporarySettings.channelPowers[1]  = 60;
        context_.temporarySettings.channelPowers[2]  = 0;
        context_.temporarySettings.channelPowers[3]  = 0;
        context_.temporarySettings.channelPowers[4]  = 0;
        context_.temporarySettings.channelPowers[5]  = 0;
        context_.temporarySettings.channelPowers[6]  = 0;
        context_.temporarySettings.channelPowers[7]  = 0;
        context_.temporarySettings.channelPowers[8]  = 0;
        context_.temporarySettings.channelPowers[9]  = 40;
        context_.temporarySettings.channelPowers[10] = 0;
        context_.temporarySettings.channelPowers[11] = 0;
        context_.temporarySettings.channelPowers[12] = 0;
        context_.temporarySettings.channelPowers[13] = 40;


        context_.masterPower = 2;


        board_.fanPwm1.setPulse(0);
        board_.fanPwm2.setPulse(0);
        isLightTime_ = false;
        isNightTime_ = true;
        applyBrightness();
    }

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
        context_.temperatures_[0] = termometers_.readTemperature(0);
        context_.temperatures_[1] = termometers_.readTemperature(1);
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
    for (std::size_t i = 0; i < context_.temperatures_.size(); ++i)
    {
        if (context_.temperatures_[i] >= TEMPERATURE_TRESHOLD && (context_.temperatures_[i] - temperaturesHistory_[i]) > TEMPERATURE_HIST)
        {
            update();

            temperaturesHistory_[i] = context_.temperatures_[i];
            logger_.info() << "Fan: 100%";
        }
        else if (context_.temperatures_[i] < TEMPERATURE_TRESHOLD && (context_.temperatures_[i] - temperaturesHistory_[i]) < -1 * TEMPERATURE_HIST)
        {
            update();
            board_.fanPwm1.setPulse(0);
            board_.fanPwm2.setPulse(0);
            temperaturesHistory_[i] = context_.temperatures_[i];
            logger_.info() << "Fan: 0%";
        }
    }
}

} // namespace app
