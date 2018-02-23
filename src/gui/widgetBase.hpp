#pragma once

#include "gui/IWidget.hpp"

namespace gui
{

class WidgetBase : public IWidget
{
public:
    WidgetBase()
        : visible_(true)
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
    }

protected:
    bool visible_;
};

} // namespace gui