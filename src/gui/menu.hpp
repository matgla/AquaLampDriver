#pragma once

#include <array>
#include <optional>

#include "display/display.hpp"
#include "gui/keys.hpp"
#include "gui/option.hpp"
#include "hal/utils/assert.hpp"
#include "utils.hpp"

#include <iostream>

namespace gui
{

template <std::size_t nrOfOptions>
class Menu : public Element
{
public:
    bool outOfViewField(int option)
    {
        return (display::Display::get()->getCharHeight() < option + 2);
    }

    void visible(int from, int to)
    {
        HAL_ASSERT_MSG(to >= from, "to must be >= from");
        HAL_ASSERT_MSG(to >= 0, "to must be >= 0");
        HAL_ASSERT_MSG(to <= currentNrOfOptions_, "to must be < all available options");
        HAL_ASSERT_MSG(from >= 0, "from must be >= 0");
        for (int i = 0; i < from; ++i)
        {
            options_[i]->visible(false);
        }
        for (; from < to; ++from)
        {
            options_[from]->visible(true);
        }
        for (; to < currentNrOfOptions_; ++to)
        {
            options_[to]->visible(false);
        }
    }

    int maxOptions()
    {
        return display::Display::get()->getCharHeight() - 2;
    }

    Menu(const char* name)
        : Element(name), currentNrOfOptions_(0), active_(true), activeOption_(0)
    {
        onKey(gui::Keys::Down, [this] {
            options_[activeOption_]->active(false);
            if (activeOption_ == currentNrOfOptions_ - 1)
            {
                activeOption_ = 0;
            }
            else
            {
                ++activeOption_;
            }

            int offset = 0;
            if (activeOption_ + 1 - maxOptions() >= 0)
            {
                offset = activeOption_ + 1 - maxOptions();
            }
            visible(offset, offset + maxOptions());

            options_[activeOption_]->active(true);
        });

        onKey(gui::Keys::Up, [this] {
            options_[activeOption_]->active(false);
            if (activeOption_ == 0)
            {
                activeOption_ = currentNrOfOptions_ - 1;
            }
            else
            {
                --activeOption_;
            }
            int offset = 0;
            if (activeOption_ + 1 - maxOptions() >= 0)
            {
                offset = activeOption_ + 1 - maxOptions();
            }
            visible(offset, offset + maxOptions());
            visible(offset, offset + maxOptions());
            options_[activeOption_]->active(true);
        });

        onKey(gui::Keys::Back, [this] { active_ = false; });
    }

    void addOption(const Option& option)
    {
        options_[currentNrOfOptions_] = option;

        if (display::Display::get()->getCharHeight() < currentNrOfOptions_ + 3)
        {
            options_[currentNrOfOptions_]->visible(false);
        }

        ++currentNrOfOptions_;

        if (currentNrOfOptions_ == 1)
        {
            options_[0]->active(true);
        }
    }

    void run(Keys key, bool isLongPressed)
    {
        bool hasAction = false;
        if (isLongPressed)
        {
            if (onLongPressedKey_[key])
            {
                onLongPressedKey_[key]();
                hasAction = true;
            }
        }
        else
        {
            if (onKey_[key])
            {
                onKey_[key]();
                hasAction = true;
            }
        }

        if (!hasAction)
        {
            for (auto& option : options_)
            {
                if (option.has_value())
                {
                    option->run(key, isLongPressed);
                }
            }
        }

        draw();
    }

    bool active() const
    {
        return active_;
    }

    void drawTitle()
    {
        display::Display::get()->print("-- ");
        if (display::Display::get()->getCharWidth() < name_.size() + 6)
        {
            display::Display::get()->print(name_.substr(0, display::Display::get()->getCharWidth() - 6).data());
        }
        else
        {
            // align
            int offset = (display::Display::get()->getCharWidth() - name_.size() - 6) / 2;
            for (int i = 0; i < offset; ++i)
            {
                display::Display::get()->print(" ");
            }

            display::Display::get()->print(name_.data());

            for (int i = 0; i < offset; ++i)
            {
                display::Display::get()->print(" ");
            }
        }
        display::Display::get()->print(" --");
    }

    void drawButtons()
    {
        display::Display::get()->setY(display::Display::get()->getHeight() - display::Images::backIcon.height);
        display::Display::get()->setX(2);
        display::Display::get()->drawImage(display::Images::backIcon);
        display::Display::get()->setX(display::Display::get()->getWidth() - display::Images::selectIcon.width - 2);
        display::Display::get()->drawImage(display::Images::selectIcon);
    }

    void draw()
    {
        display::Display::get()->clear(display::Colors::OFF);
        drawTitle();

        for (auto& option : options_)
        {
            if (option.has_value())
            {
                option->draw();
            }
        }

        drawButtons();
    }

protected:
    std::array<std::optional<Option>, nrOfOptions> options_;
    int currentNrOfOptions_;
    bool active_;
    int activeOption_;
};


/*
Option.onButton(left, [](){drawLeft()})
Option.onDraw()
menu.addOption("About");


*/

} // namespace gui
