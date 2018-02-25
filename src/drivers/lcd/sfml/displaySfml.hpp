#pragma once

#include <SFML/Graphics.hpp>

#include "display/colors.hpp"
#include "drivers/lcd/displayDriver.hpp"
#include "logger/logger.hpp"

namespace drivers
{
namespace lcd
{

class DisplaySfml : public DisplayDriver
{
public:
    DisplaySfml();

    void display() override;
    int getHeight() const override;
    int getWidth() const override;
    void setPixel(int x, int y, display::Colors color = display::Colors::BLACK) override;

protected:
    static sf::Color convertToSfColor(display::Colors color);

    logger::Logger logger_;
    sf::Image buffer_;
};

} // namespace lcd
} // namespace drivers
