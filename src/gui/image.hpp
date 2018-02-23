#pragma once

#include "display/display.hpp"
#include "display/images.hpp"
#include "gui/element.hpp"
#include "gui/primitives/IShape.hpp"
#include "gui/widgetBase.hpp"
namespace gui
{

class Image : public WidgetBase
{
public:
    Image(const primitives::IShape& shape)
        : shape_(shape)
    {
    }

    void draw() const override
    {
        shape_.draw();
    }

private:
    const primitives::IShape& shape_;
};
// class Image : public Element
// {
// public:
//     Image(const display::Image& image)
//         : Element(""), image_(image)
//     {
//     }

//     void onDraw() override
//     {
//         if (customDraw_)
//         {
//             customDraw_(image_);
//         }
//         else
//         {
//             display::Display::get()->drawImage(image_);
//         }
//     }

//     void setDraw(const std::function<void(const display::Image&)>& draw)
//     {
//         customDraw_ = draw;
//     }

// private:
//     const display::Image& image_;
//     std::function<void(const display::Image&)> customDraw_;
// };

} // namespace gui