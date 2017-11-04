#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

namespace bsp
{
namespace x86
{

class Window
{
public:
    static Window& get();
    sf::RenderWindow& window();
    void run();
    void add(const std::string& name, std::unique_ptr<sf::Shape> shape);

    void setDisplayBox(const sf::RectangleShape& displayBox);
    void setDisplay(const sf::Texture& display);
    int getHeight();
    int getWidth();

private:
    Window();

    sf::RectangleShape displayBox_;
    sf::Texture display_;
    std::map<std::string, std::unique_ptr<sf::Shape>> shapes_;
};

} // namespace x86
} // namespace bsp
