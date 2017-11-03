#pragma once

#include "timer/timeoutTimer.hpp"

namespace bsp
{
    
enum class Buttons
{
    Up,
    Down,
    Left,
    Right,
    Select,
    Back
};

template <Buttons button>
class Button
{
  public:
    Button()
    {
        static_assert(sizeof(button) == 0, "Default constructor can't be used");
    }

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
    static bool isPinPressed()
    {
        static_assert(sizeof(button) == 0, "Default  can't be used");
    }
    
    bool isLong_ = false;
    timer::TimeoutTimer timer_;
    timer::TimeoutTimer isLongTimer_;
};

} // namespace bsp