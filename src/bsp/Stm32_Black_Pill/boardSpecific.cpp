#include "bsp/board.hpp"

#include <stm32f10x.h>

namespace bsp
{

void BoardInit()
{
    SystemInit();
}

void Board::run()
{
}

bool Board::exit()
{
    return false;
}
} // namespace bsp
