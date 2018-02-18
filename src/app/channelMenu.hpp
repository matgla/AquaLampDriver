#pragma once

#include <cstdint>

#include "app/contextInterface.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"

#include "gui/menu.hpp"

namespace app
{

class ChannelMenu
{

public:
    ChannelMenu(display::Display& display, bsp::Board& board, IContext& context)
        : menu_("Channel")
    {
    }

    enum class State : uint8_t
    {
        Close,
        ChangeCurrentPower,
        ChannelSelect,
        ChangePower,
        SetDayTime,
        SetNightTime,
        SetSunriseLength
    };

    void start()
    {
    }

    State run()
    {
        menu_.draw();
        return State::Close;
    }

private:
    gui::Menu<1> menu_;


    //     enum class SubState : uint8_t
    //     {
    //         None,
    //         ChangeDayPower,
    //         ChangeNightPower,
    //         SetHours,
    //         SetMinutes,
    //         SetSeconds
    //     };

    //     State run();
    //     void start();

    // protected:
    //     void changePower(uint8_t& power);
    //     void onShow();
    //     void drawPrefix(State state);
    //     void onSelect();
    //     void onChannelSelect();
    //     void onChangePower();
    //     void onChangeDayPower();
    //     void onChangeNightPower();
    //     void onSetDayTime();
    //     void onSetNightTime();

    //     display::Display& display_;
    //     bsp::Board& board_;
    //     IContext& context_;
    //     uint8_t currentChannel_;
    //     uint8_t selection_;
    //     State state_;
    //     SubState subState_;
};

} // namespace app