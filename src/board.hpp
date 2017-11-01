#pragma once

#include "timer/timeoutTimer.hpp"

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

#define GPIO_IN_READ_DELAY 100

template <Buttons button>
class Button
{
  public:
    Button();

    bool isPressed()
    {
        timer_.run();
        if (timer_.enabled())
        {
            return false;
        }

        if (isPinPressed())
        {
            timer_.start(GPIO_IN_READ_DELAY);
            return true;
        }
        return false;
    }

  private:
    static bool isPinPressed();
    timer::TimeoutTimer timer_;
};

template <Leds led>
class Led
{
  public:
    Led();
    static void on();
    static void off();
};

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
};