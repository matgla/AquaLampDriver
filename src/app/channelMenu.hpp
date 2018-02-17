#pragma once

#include "bsp/board.hpp"
#include "display/display.hpp"
#include "app/contextInterface.hpp"

namespace app
{

class ChannelMenu
{
public:
    ChannelMenu(display::Display& display, bsp::Board& board, IContext& context);
    enum class State : uint8_t
    {
        Close,
        ChannelSelect,
        ChangeDayPower,
        ChangeNightPower,
        ChangePower,
        SetDayTime,
        SetNightTime
    };

    State run();
    void start();
protected:
    void changePower(u8& power);
    void onShow();
    void drawPrefix(State state);
    void onSelect();
    void onChannelSelect();
    void onChangePower();
    void onChangeDayPower();
    void onChangeNightPower();
    void onSetDayTime();
    void onSetNightTime();

    display::Display& display_;
    bsp::Board& board_;
    IContext& context_;
    uint8_t currentChannel_;
    uint8_t selection_;
    State state_;
};

} // namespace app