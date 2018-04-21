#pragma once

#include "gui/widgetBase.hpp"

namespace gui
{

class Button : public WidgetBase
{
public:
    virtual void draw() final
    {
        if (visible_)
        {
            // draw smth
        }
    }
};

} // namespace gui
