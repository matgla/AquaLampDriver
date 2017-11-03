#include "bsp/board.hpp"

#include <SFML/Graphics.hpp>

namespace bsp
{

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

void BoardInit()
{
}

void Board::run()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear();
    window.display();
}

bool Board::exit()
{
    return !window.isOpen();
}

} // namespace bsp
