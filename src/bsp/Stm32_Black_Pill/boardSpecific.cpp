#include "bsp/board.hpp"

#include <stm32f10x.h>

namespace bsp
{

void BoardInit()
{
    SystemInit();
}
    
} // namespace bsp
