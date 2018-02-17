#include "app/channelMenu.hpp"

#include "hal/time/sleep.hpp"

namespace app
{

ChannelMenu::ChannelMenu(display::Display& display, bsp::Board& board, IContext& context) 
: display_(display),
board_(board),
context_(context),
currentChannel_(0),
selection_(1),
state_(ChannelMenu::State::Close)
{    
}

void ChannelMenu::start()
{
    state_ = State::ChannelSelect;
}

void ChannelMenu::onChangePower()
{
    if (board_.downButton.isPressed())
    {
        state_ = State::SetDayTime;
        return;
    }
    
    if (board_.upButton.isPressed())
    {
        state_ = State::ChannelSelect;
        return;
    }

    if (board_.rightButton.isPressed())
    {
        state_ = State::ChangeDayPower;
        return;
    }
}

void ChannelMenu::onSetDayTime()
{

    if (board_.downButton.isPressed())
    {
        state_ = State::SetNightTime;
        return;
    }
    
    if (board_.upButton.isPressed())
    {
        state_ = State::ChangePower;
        return;
    }
}

void ChannelMenu::onSetNightTime()
{
    if (board_.downButton.isPressed())
    {
        state_ = State::ChannelSelect;
        return;
    }
    
    if (board_.upButton.isPressed())
    {
        state_ = State::SetDayTime;
        return;
    }
}

void ChannelMenu::changePower(u8& power)
{
    if (board_.upButton.isPressed())
    {
        if (power + 1 >= 100)
        {
            power = 100;
            return;
        }
        power += 1;
        return;
    }
    if (board_.downButton.isPressed())
    {
        if (power <= 1)
        {
            power = 0;
            return;
        }
        power -= 1;
        return;
    }

    if (board_.upButton.isLongPressed())
    {
        hal::time::msleep(100);
        if (power + 5 >= 100)
        {
            power = 100;
            return;
        }
        power += 5;
        return;
    }
    if (board_.downButton.isLongPressed())
    {
        hal::time::msleep(100);        
        if (power <= 5)
        {
            power = 0;
            return;
        }
        power -= 5;
        return;
    }
}

void ChannelMenu::onChangeDayPower()
{
    
    if (board_.leftButton.isPressed())
    {
        state_ = State::ChangePower;
        return;
    }

    if (board_.rightButton.isPressed())
    {
        state_ = State::ChangeNightPower;
        return;
    }

    changePower(context_.getAllChannels()[currentChannel_].dayPower());
}

void ChannelMenu::onChangeNightPower()
{
    if (board_.leftButton.isPressed())
    {
        state_ = State::ChangeDayPower;
        return;
    }
    changePower(context_.getAllChannels()[currentChannel_].nightPower());
}

ChannelMenu::State ChannelMenu::run()
{
    if (board_.backButton.isPressed())
    {
        return ChannelMenu::State::Close;
    }

    switch (state_)
    {
        case State::ChannelSelect:
        onChannelSelect();
        break;
        case State::ChangePower:
        onChangePower();
        break;
        case State::ChangeDayPower:
        onChangeDayPower();
        break;
        case State::ChangeNightPower:
        onChangeNightPower();
        break;
        case State::SetDayTime:
        onSetDayTime();
        break;
        case State::SetNightTime:
        onSetNightTime();
        break;
        case State::Close:
        break;
    }
    
    onShow();
    return state_;
}

void ChannelMenu::onChannelSelect()
{
    if (board_.leftButton.isPressed())
    {
        if (currentChannel_ == 0)
        {
            currentChannel_ = 13;
            return;
        }
        --currentChannel_;
        return;
    }

    if (board_.rightButton.isPressed())
    {
        if (currentChannel_ == 13)
        {
            currentChannel_ = 0;
            return;
        }
        ++currentChannel_;
        return;
    }

    if (board_.upButton.isPressed())
    {
        state_ = State::SetNightTime;
        return;
    }

    if (board_.downButton.isPressed())
    {
        state_ = State::ChangePower;
        return;
    }
}

void ChannelMenu::drawPrefix(State state)
{
    if (state_ == state)
    {
        display_.drawImage(display::Images::fullTriangle);
    } 
    else
    {
        display_.drawImage(display::Images::emptyTriangle);
    }
    display_.incrementCursorX(1);
}

void ChannelMenu::onShow()
{
    display_.clear(display::Colors::OFF);
    drawPrefix(State::ChannelSelect);    
    char buffer[5];
    display_.print("Channel: ");

    if (currentChannel_ == 0)
    {
        display_.print(" M\n");
    }
    else
    {
        utils::writeToBufferAligned(buffer, currentChannel_, '\0', 2, ' ');
        display_.print(buffer);
        display_.print("\n");
    }
   // display_.print("    D    N\n");    
    display_.incrementCursorY(2);
    
    if (State::ChangeDayPower == state_ || State::ChangeNightPower == state_)
    {
        drawPrefix(state_);
    }
    else
    {
        drawPrefix(State::ChangePower);
    }

    utils::writeToBufferAligned(buffer, context_.getAllChannels()[currentChannel_].dayPower(), '\0', 3, ' ');
    display_.print("P:");
    display_.decrementCursorY(2);
    display_.drawImage(display::Images::Sun);
    display_.incrementCursorY(2);
    display_.incrementCursorX(2);
    
    if (state_ == State::ChangeDayPower)
    {
        display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
    }
    else
    {
        display_.print(buffer);
    }
    display_.print("%");

    display_.incrementCursorX(2);
    display_.decrementCursorY(2);
    display_.drawImage(display::Images::Moon);
    display_.incrementCursorY(2);
    display_.incrementCursorX(1);
    
    utils::writeToBufferAligned(buffer, context_.getAllChannels()[currentChannel_].nightPower(), '\0', 3, ' ');
    
    if (state_ == State::ChangeNightPower)
    {
        display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
    }
    else
    {
        display_.print(buffer);
    }
    display_.print("%\n");

    display_.incrementCursorY(1);
    drawPrefix(State::SetDayTime);
    display_.drawImage(display::Images::Sun);
    display_.incrementCursorY(2);
    display_.print(" 00:00:00\n");
    drawPrefix(State::SetNightTime);
    display_.drawImage(display::Images::Moon);
    display_.incrementCursorY(1);    
    display_.incrementCursorX(4);    
    display_.print(" 00:00:00\n");    
    display_.setY(48 - display::Images::backIcon.height);
    display_.setX(2);
    display_.drawImage(display::Images::backIcon);
    display_.setX(84 - display::Images::selectIcon.width - 2);
    display_.drawImage(display::Images::selectIcon);

}

} // namespace app
