#pragma once

#include <cstdint>

#include "app/channelMenu.hpp"
#include "app/contextInterface.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"

namespace app
{

class MainMenu : public gui::Menu<5>
{
public:
    MainMenu(bsp::Board& board, IContext& context);
};

} // namespace app
