#include "app/menu.hpp"

namespace app
{

Menu::Menu(display::Display& display, bsp::Board& board, IContext& context) : 
    selection_(1), display_(display), board_(board), channelMenu_(display, board, context) 
{
}

void Menu::onShow()
{
    display_.clear(display::Colors::OFF);
    drawPrefix(1);
    display_.print("1.Channel\n");
    drawPrefix(2);
    display_.print("2.Time\n");
    drawPrefix(3);
    display_.print("3.General\n");
    drawPrefix(4);
    display_.print("4.Effects\n");
    drawPrefix(5);
    display_.print("5.About\n");
    display_.setY(48 - display::Images::backIcon.height);
    display_.setX(2);
    display_.drawImage(display::Images::backIcon);
    display_.setX(84 - display::Images::selectIcon.width - 2);
    display_.drawImage(display::Images::selectIcon);

}

void Menu::onSelect()
{
    switch (selection_)
    {
        case 1:
            channelMenu_.start();
            channelMenu_.run();
            state_ = State::ChannelMenu;
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
    }
}

void Menu::drawPrefix(uint8_t selection)
{
    if (selection_ == selection)
    {
        display_.drawImage(display::Images::fullTriangle);
    } 
    else
    {
        display_.drawImage(display::Images::emptyTriangle);
    }
    display_.incrementCursorX(1);
}

void Menu::start()
{
    state_ = State::Running;
}

void Menu::onRun()
{
    if (board_.backButton.isPressed())
    {
        state_ = State::Close;
    }
    if (board_.downButton.isPressed())
    {
        if (selection_ >= 5)
        {
            selection_ = 1;
        }
        else 
        {
            ++selection_;
        }
    }

    if (board_.upButton.isPressed())
    {
        if (selection_ == 1)
        {
            selection_ = 5;
        }
        else 
        {
            --selection_;
        }
    }

    if (board_.selectButton.isPressed())
    {
        onSelect();
    }
    onShow();
}

Menu::State Menu::run()
{
    switch (state_)
    {
        case State::Running:
        {
            onRun();
        } break;
        case State::ChannelMenu:
        {
            if (ChannelMenu::State::Close == channelMenu_.run())
            {
                state_ = State::Running;
            }
        } break;
        case State::Close:
        {

        } break;
    }
    return state_;
}

} // namespace app
