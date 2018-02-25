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

    virtual void display()                                                              = 0;
    virtual int getHeight() const                                                       = 0;
    virtual int getWidth() const                                                        = 0;
    virtual void setPixel(int x, int y, display::Colors color = display::Colors::BLACK) = 0;
};

} // namespace lcd
} // namespace drivers
