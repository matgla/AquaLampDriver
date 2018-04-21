#pragma once

#include "gui/IWidget.hpp"
#include "gui/vector2d.hpp"

namespace gui
{

class WidgetBase : public IWidget
{
public:
    WidgetBase(Vector2d pos)
        : visible_(true)
        , position_(pos)
    {
    }

    virtual void show() final
    {
        visible_ = true;
    }

    virtual void hide() final
    {
        visible_ = false;
    }

    virtual void move(Vector2d pos)
    {
        if (visible_)
        {
            hide();
            position_ = pos;
            show();
            draw();    
        }
        else
        {
            position_ = pos;
        }
    }

protected:
    bool visible_;
    Vector2d position_;
};

} // namespace gui