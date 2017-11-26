#include "bsp/board.hpp"

#include <stm32f10x.h>

namespace bsp
{

void BoardInit()
{
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
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
