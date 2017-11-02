#pragma once

#include "timer/timeoutTimer.hpp"

#include "hal/core/backupRegisters.hpp"
#include "logger/logger.hpp"

enum class Buttons
{
    Up,
    Down,
    Left,
    Right,
    Select,
    Back
};

enum class Leds
{
    Led1
};

#define GPIO_IN_READ_DELAY 300
#define TIME_TO_LONG_PUSH 1000

template <Buttons button>
class Button
{
  public:
    Button();

    bool isPressed()
    {
        timer_.run();
        isLongTimer_.run();
        bool wasPressed = isPinPressed();
        if (!wasPressed && timer_.elapsed() > 100)
        {
            isLongTimer_.cancel();
            isLong_ = false;
            timer_.cancel();
        }

        if (timer_.enabled())
        {
            return false;
        }

        if (wasPressed)
        {
            timer_.start(GPIO_IN_READ_DELAY);
            if (!isLongTimer_.enabled())
            {
                isLongTimer_.start(TIME_TO_LONG_PUSH, [this] { isLong_ = true; });
            }

            return true;
        }

        return false;
    }

    bool isLongPressed()
    {
        return isLong_;
    }

  private:
    static bool isPinPressed();
    bool isLong_ = false;
    timer::TimeoutTimer timer_;
    timer::TimeoutTimer isLongTimer_;
};

template <Leds led>
class Led
{
  public:
    Led();
    static void on();
    static void off();
};


void CoreInit();


class Board
{
  public:
    Board();

    Button<Buttons::Left> leftButton;
    Button<Buttons::Right> rightButton;
    Button<Buttons::Up> upButton;
    Button<Buttons::Down> downButton;
    Button<Buttons::Select> selectButton;
    Button<Buttons::Back> backButton;

    Led<Leds::Led1> led;

    hal::core::BackupRegisters& registers;

  private:
    logger::Logger logger_;
};