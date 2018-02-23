#include "app/app.hpp"

#include <cmath>

#include "app/statemachines/events.hpp"
#include "bsp/board.hpp"
#include "gui/keys.hpp"
#include "hal/core/criticalSection.hpp"
#include "hal/time/rtc.hpp"
#include "hal/time/watchdog.hpp"
#include "logger/logger.hpp"

namespace app
{
App::App(display::Display& display, bsp::Board& board, app::IContext& context)
    : context_(context), lightController_(context), logger_("App"), board_(board), display_(display), state_(App::State::Off), backlight_(true), menu_(board, context), window_({0, 0}, 0, 0, "Main")

{
    window_.fullscreen(true);
}

//     : logger_("App"),
//       display_(display),
//       board_(board),
//       context_(board, display, logger_),
//       backlight_(false),
//     //   statemachine_(context_),
//       termometers_(board),
//       lightState_(LightStates::Off)
// {
// }

void App::applyBrightness()
{
    board_.ledPwm1.setPulse(context_.getAllChannels()[1].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm2.setPulse(context_.getAllChannels()[2].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm3.setPulse(context_.getAllChannels()[3].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm4.setPulse(context_.getAllChannels()[4].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm5.setPulse(context_.getAllChannels()[5].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm6.setPulse(context_.getAllChannels()[6].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm7.setPulse(context_.getAllChannels()[7].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm8.setPulse(context_.getAllChannels()[8].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm9.setPulse(context_.getAllChannels()[9].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm10.setPulse(context_.getAllChannels()[10].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm11.setPulse(context_.getAllChannels()[11].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm12.setPulse(context_.getAllChannels()[12].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
    board_.ledPwm13.setPulse(context_.getAllChannels()[13].currentPower() * (static_cast<float>(context_.masterChannel().currentPower()) / 100));
}

void App::start()
{
    // TODO: This should be stored in flash
    // if (hal::core::BackupRegisters::get().isFirstStartup())
    // {
    //     logger_.info() << "Settings initializing";
    //     // context_.initSettings();
    // }

    // delayedBacklightOff();
    display_.clear(display::Colors::OFF);
    logger_.info() << "Startup";

    // hal::time::Rtc::get().setSecondsHandler([this] {
    //     this->update();
    // });

    board_.led.on();
    // board_.registers.startupDone();

    // hal::time::WatchDog::enable(2000); // 2s

    logger_.info() << "Started";

    // context_.readSettings();
    // context_.temporarySettings = context_.settings;
    // if (!isLightTime())
    // {
    //     context_.masterPower = 0;
    // }
    // applyBrightness();
    state_ = State::Show;
}

void App::delayedBacklightOff()
{
    if (backlight_ == false)
    {
        display_.backlightOn();
        // backlightTimer_ = context_.timerManager.setTimeout(10000, [this] {
        //     display_.backlightOff();
        //     logger_.info() << "Backlight off";
        //     backlight_ = false;
        // });
        backlight_ = true;
    }
    else
    {
        // auto* timer = context_.timerManager.getTimeoutTimer(backlightTimer_);
        // if (timer)
        // {
        //     timer->restart(10000);
        // }
    }
}

void App::onShow()
{
    if (board_.downButton.isPressed())
    {
        delayedBacklightOff();
        state_ = State::Menu;
        std::cout << "Menu" << std::endl;

        return;
    }
    if (board_.upButton.isPressed())
    {
        delayedBacklightOff();
        state_ = State::Menu;
        std::cout << "Menu" << std::endl;

        return;
    }
    if (board_.leftButton.isPressed())
    {
        delayedBacklightOff();
        lightController_.master().decreasePower(1);
    }
    if (board_.rightButton.isPressed())
    {
        delayedBacklightOff();
        lightController_.master().increasePower(1);
    }
    if (board_.leftButton.isLongPressed())
    {
        delayedBacklightOff();
        lightController_.master().decreasePower(5);
        hal::time::msleep(100);
    }
    if (board_.rightButton.isLongPressed())
    {
        delayedBacklightOff();
        lightController_.master().increasePower(5);
        hal::time::msleep(100);
    }
    if (board_.selectButton.isPressed())
    {
        delayedBacklightOff();
        logger_.info() << "select";
    }
    if (board_.backButton.isPressed())
    {
        delayedBacklightOff();
        lightController_.forceLight(false);
    }

    display_.clear(display::Colors::OFF);
    constexpr const int TimeBufferSize = 9;
    constexpr const int DateBufferSize = 12;
    char timeBuffer[TimeBufferSize];
    char dateBuffer[DateBufferSize];
    auto t                 = std::time(nullptr);
    struct tm* currentTime = std::localtime(&t);
    utils::formatDate(dateBuffer, DateBufferSize, currentTime);
    utils::formatTime(timeBuffer, TimeBufferSize, currentTime);
    display_.print("");
    display_.print(dateBuffer);
    if (lightController_.isForced())
    {
        display_.print("  F");
    }
    display_.print("\n");
    display_.print(timeBuffer);
    display_.print("\nPower: ");
    char buffer[5];
    utils::writeToBufferAligned(buffer, context_.masterChannel().currentPower(), '\0', 3, ' ');
    display_.print(buffer);


    // display_.print(" %\nTL: ");
    // // float temp = context.temperatures_[0];
    // // auto conv = utils::floatToInts(temp, 1);
    // // utils::itoa(conv.first, buffer);
    // display_.print(buffer);
    // display_.print(".");
    // // utils::itoa(conv.second, buffer);
    // display_.print(buffer);
    // // temp = context.temperatures_[1];
    // display_.print("  TR: ");
    // // conv = utils::floatToInts(temp, 1);
    // // utils::itoa(conv.first, buffer);
    // display_.print(buffer);
    // display_.print(".");
    // utils::itoa(conv.second, buffer);
    // display_.print(buffer);
}

void App::updateKey()
{
    if (board_.leftButton.isPressed())
    {
        key_              = gui::Keys::Left;
        isLongPressedKey_ = false;
        return;
    }

    if (board_.upButton.isPressed())
    {
        key_              = gui::Keys::Up;
        isLongPressedKey_ = false;
        return;
    }

    if (board_.rightButton.isPressed())
    {
        key_              = gui::Keys::Right;
        isLongPressedKey_ = false;
        return;
    }

    if (board_.downButton.isPressed())
    {
        key_              = gui::Keys::Down;
        isLongPressedKey_ = false;
        return;
    }

    if (board_.selectButton.isPressed())
    {
        key_              = gui::Keys::Select;
        isLongPressedKey_ = false;
        return;
    }

    if (board_.backButton.isPressed())
    {
        key_              = gui::Keys::Back;
        isLongPressedKey_ = false;
        return;
    }

    if (board_.leftButton.isLongPressed())
    {
        key_              = gui::Keys::Left;
        isLongPressedKey_ = true;
        return;
    }

    if (board_.upButton.isLongPressed())
    {
        key_              = gui::Keys::Up;
        isLongPressedKey_ = true;
        return;
    }

    if (board_.rightButton.isLongPressed())
    {
        key_              = gui::Keys::Right;
        isLongPressedKey_ = true;
        return;
    }

    if (board_.downButton.isLongPressed())
    {
        key_              = gui::Keys::Down;
        isLongPressedKey_ = true;
        return;
    }

    if (board_.selectButton.isLongPressed())
    {
        key_              = gui::Keys::Select;
        isLongPressedKey_ = true;
        return;
    }

    if (board_.backButton.isLongPressed())
    {
        key_              = gui::Keys::Back;
        isLongPressedKey_ = true;
        return;
    }

    key_              = gui::Keys::None;
    isLongPressedKey_ = false;
}

void App::run()
{
    // using namespace statemachines;
    // context_.timerManager.setInterval(1000, [this]() {
    //     termometers_.measureTemperature();
    //     // context_.temperatures_[0] = termometers_.readTemperature(0);
    //     // context_.temperatures_[1] = termometers_.readTemperature(1);
    // });

    while (!board_.exit())
    {
        window_.draw();

        // switch (state_)
        // {
        //     case State::Off:
        //         break;
        //     case State::Show:
        //         onShow();
        //         break;
        //     case State::Menu:
        //         updateKey();
        //         menu_.run(key_, isLongPressedKey_);
        //         if (!menu_.active())
        //         {
        //             state_ = State::Show;
        //             std::cout << "Menu off" << std::endl;
        //         }
        //         break;
        // }
        // hal::time::WatchDog::feed();


        // // measure temperature

        // processTemperature();

        // make actions
        board_.run();
        // context_.timerManager.run();
    }
    // hal::time::Rtc::get().stop();
}

// void App::processTemperature()
// {
//     // for (std::size_t i = 0; i < context_.temperatures_.size(); ++i)
//     // {
//     //     if (context_.temperatures_[i] >= TEMPERATURE_TRESHOLD && (context_.temperatures_[i] - temperaturesHistory_[i]) > TEMPERATURE_HIST)
//     //     {
//     //         update();
//     //         board_.fanPwm1.setPulse(100);
//     //         board_.fanPwm2.setPulse(100);
//     //         temperaturesHistory_[i] = context_.temperatures_[i];
//     //         logger_.info() << "Fan: 100%";
//     //     }
//     //     else if (context_.temperatures_[i] < TEMPERATURE_TRESHOLD && (context_.temperatures_[i] - temperaturesHistory_[i]) < -1 * TEMPERATURE_HIST)
//     //     {
//     //         update();
//     //         board_.fanPwm1.setPulse(0);
//     //         board_.fanPwm2.setPulse(0);
//     //         temperaturesHistory_[i] = context_.temperatures_[i];
//     //         logger_.info() << "Fan: 0%";
//     //     }
//     // }
// }

} // namespace app
