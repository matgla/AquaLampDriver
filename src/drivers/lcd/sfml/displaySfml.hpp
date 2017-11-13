#pragma once

#include <SFML/Graphics.hpp>

#include "display/colors.hpp"
#include "drivers/lcd/displayDriver.hpp"
#include "logger/Logger.hpp"

namespace drivers
{
namespace lcd
{

class DisplaySfml : public DisplayDriver
{
public:
    DisplaySfml();

    void display() const override;
    u16 getHeight() const override;
    u16 getWidth() const override;
    void setPixel(u16 x, u16 y, display::Colors color = display::Colors::BLACK) override;

protected:
    static sf::Color convertToSfColor(display::Colors color);

    logger::Logger logger_;
    sf::Image buffer_;
};

} // namespace lcd
} // namespace drivers
