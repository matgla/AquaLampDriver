#pragma once

#include <cstdint>

#include "app/channelMenu.hpp"
#include "app/contextInterface.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"
#include "gui/keys.hpp"

#include <iostream>

namespace app
{

class MainMenu : public gui::Menu<5>
{
public:
    MainMenu(bsp::Board& board, IContext& context);

    // void run(gui::Keys key, bool isLongPressed) override
    // {
    //     if (currentMenu_ == this)
    //     {
    //         std::cerr << "no to lecimy z koksem" << std::endl;
    //         onRun(key, isLongPressed);
    //     }
    //     else
    //     {
    //         currentMenu_->run(key, isLongPressed);
    //     }
    // }

protected:
    void createChannelsMenu();


    gui::Menu<5> channelsMenu_;
    gui::Element* currentMenu_;
};

} // namespace app
