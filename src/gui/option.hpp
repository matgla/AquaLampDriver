#pragma once

#include <experimental/string_view>

#include "display/display.hpp"
#include "display/images.hpp"
#include "gui/element.hpp"

namespace gui
{

class Option : public Element
{
public:
    Option(const char* name)
        : Element(name)
    {
    }

    Option()
        : Element("")
    {
    }

    void drawArrow()
    {
        if (active_)
        {
            display::Display::get()->drawImage(display::Images::fullTriangle);
        }
        else
        {
            display::Display::get()->drawImage(display::Images::emptyTriangle);
        }
    }

    void onDraw() override
    {
        if (!visible_)
        {
            return;
        }
        drawArrow();
        display::Display::get()->print(" ");
        if (next_)
        {
            next_->draw();
        }
        display::Display::get()->print("\n");
    }

protected:
};

} // namespace gui
