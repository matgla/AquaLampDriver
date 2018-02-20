#pragma once

#include "display/display.hpp"
#include "gui/element.hpp"

namespace gui
{

template <int x, int y = 0>
class MoveCursor : public Element
{
public:
    MoveCursor()
        : Element("")
    {
    }

    void onDraw() override
    {
        if constexpr (x < 0)
        {
            display::Display::get()->decrementCursorX(-1 * x);
        }
        else
        {
            display::Display::get()->incrementCursorX(x);
        }

        if constexpr (y < 0)
        {
            display::Display::get()->decrementCursorY(-1 * y);
        }
        else
        {
            display::Display::get()->incrementCursorY(y);
        }
    }
};

} // namespace gui