#include "hw_utils.h"
#include "stm32includes.hpp"
#include <stdint.h>
#include <stdio.h>
extern uint32_t SystemCoreClock;

u8 initalizeSysTick(u32 time_us) {
	if(time_us == 0) return false;
	printf("Core clock: %d", SystemCoreClock);
	if(SysTick_Config(SystemCoreClock/1000000*time_us) != 0) {
		return false;
	}
	return true;
}