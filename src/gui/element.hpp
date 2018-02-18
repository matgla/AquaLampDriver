#pragma once

#include <array>
#include <experimental/string_view>
#include <functional>


#include "gui/keys.hpp"
#include "logger/logger.hpp"

namespace gui
{

class Element
{
public:
    using ActionType = std::function<void()>;

    Element(const char* name)
        : name_(name),
          visible_(true),
          active_(false),
          next_(nullptr)
    {
    }

    virtual ~Element() = default;

    virtual void onDraw(){};

    void onKey(Keys key, ActionType action)
    {
        onKey_[key] = action;
    }

    void onLongPressedKey(Keys key, ActionType action)
    {
        onLongPressedKey_[key] = action;
    }

    void active(bool active)
    {
        active_ = active;
    }

    void visible(bool visible)
    {
        visible_ = visible;
    }

    void onRun(Keys key, bool isLongPressed)
    {
        if (isLongPressed)
        {
            if (onLongPressedKey_[key])
            {
                onLongPressedKey_[key]();
            }
        }
        else
        {
            if (onKey_[key])
            {
                onKey_[key]();
            }
        }
        draw();
    }
    virtual void run(Keys key, bool isLongPressed)
    {
        onRun(key, isLongPressed);
    }

    void draw()
    {
        if (visible_)
        {
            onDraw();
        }
    }

    virtual int height()
    {
        return display::Display::get()->getFont().height;
    }

    virtual int width()
    {
        return display::Display::get()->getFont().width;
    }

    void next(Element* element)
    {
        next_ = element;
    }

protected:
    std::experimental::string_view name_;
    std::array<ActionType, gui::KeysSize> onKey_;
    std::array<ActionType, gui::KeysSize> onLongPressedKey_;

    bool visible_;
    bool active_;
    Element* next_;
};

} // namespace gui