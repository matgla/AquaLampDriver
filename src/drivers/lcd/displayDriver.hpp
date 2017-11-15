#pragma once

#include <gsl/span>

#include "display/colors.hpp"
#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace drivers
{
namespace lcd
{

class DisplayDriver
{
public:
    virtual ~DisplayDriver() = default;

    virtual void display() = 0;
    virtual u16 getHeight() const = 0;
    virtual u16 getWidth() const = 0;
    virtual void setPixel(u16 x, u16 y, display::Colors color = display::Colors::BLACK) = 0;
};

} // namespace lcd
} // namespace drivers
