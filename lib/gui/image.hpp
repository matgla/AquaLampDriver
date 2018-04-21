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
    Image(Vector2d pos, const primitives::IShape& shape)
        : WidgetBase(pos)
        , shape_(shape)
    {
    }

    void draw() const override
    {
        shape_.draw();
    }

private:
    const primitives::IShape& shape_;
};

} // namespace gui