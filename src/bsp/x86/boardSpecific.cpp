#include "bsp/board.hpp"

#include "bsp/x86/window.hpp"

namespace bsp
{

void BoardInit()
{
}

void Board::run()
{
    x86::Window::get().run();
}

bool Board::exit()
{
    return !x86::Window::get().window().isOpen();
}

} // namespace bsp
