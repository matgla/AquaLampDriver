#pragma once

#include <cstdint>

#include "app/channelMenu.hpp"
#include "app/contextInterface.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"

namespace app
{

class MainMenu : public gui::Menu
{
public:
    MainMenu(bsp::Board& board, IContext& context);

protected:
    void createChannelsMenu();

    gui::Menu channelsMenu_;
};

} // namespace app
