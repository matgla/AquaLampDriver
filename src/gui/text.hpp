#pragma once

#include <string_view>

#include "gui/element.hpp"

namespace gui
{

class Text : public Element
{
public:
    Text(const char* text = "")
        : Element(""), text_(text)
    {
    }

    void onDraw() override
    {
        if (text_.size() * (display::Display::get()->getFont().width + 1) <= display::Display::get()->getWidthToEnd())
        {
            display::Display::get()->print(text_.data());
        }
        else
        {
            display::Display::get()->print(text_.substr(0, display::Display::get()->getWidthToEnd() / display::Display::get()->getFont().width).data());
        }
    }

protected:
    std::string_view text_;
};

} // namespace gui
