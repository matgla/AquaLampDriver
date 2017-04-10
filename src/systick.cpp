#include "systick.hpp"

volatile unsigned long ticks = 0;

void SysTick_Handler(void)  {
    ++ticks;
    if (ticks % 100 == 0)
    {
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }
}

unsigned long getTicks()
{
    return ticks;
}