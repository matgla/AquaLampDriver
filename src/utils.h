#pragma once

#include <stdint.h>
#include "types.h"

void DelayInit(u32 systemCoreClock) __attribute__((optimize("-O0")));;
void Delay(u32 delay_ms) __attribute__((optimize("-O0")));;
void DelayUs(u32 delay_us) __attribute__((optimize("-O0")));;
void DelayS(u32 delay_s) __attribute__((optimize("-O0")));;

