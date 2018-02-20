#pragma once

#include <experimental/string_view>
#include <optional>

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
        drawArrow();
        display::Display::get()->print(" ");
    }

    int height() override
    {
        return height_.value_or(Element::height());
    }

    void height(int height)
    {
        height_ = height;
    }

protected:
    std::optional<int> height_;
};

} // namespace gui
