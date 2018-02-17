#pragma once

#include <cstdint>

#include "bsp/board.hpp"
#include "display/display.hpp"
#include "app/contextInterface.hpp"
#include "app/channelMenu.hpp"

namespace app
{

class Menu 
{
public:
    Menu(display::Display& display, bsp::Board& board, IContext& context);
    enum class State
    {
        Close,
        Running,
        ChannelMenu
    };

    State run();
    void start();
protected:
    void onShow();
    void drawPrefix(uint8_t selection);
    void onSelect();
    void onRun();
    
    uint8_t selection_;
    display::Display& display_;
    bsp::Board& board_;
    ChannelMenu channelMenu_;
    State state_;
};

} // namespace app
