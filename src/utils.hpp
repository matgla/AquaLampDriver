#pragma once

#include "types.h"
#include <cstring>
#include <stdint.h>


void DelayInit(u32 systemCoreClock) __attribute__((optimize("-O0")));
void Delay(u32 delay_ms) __attribute__((optimize("-O0")));
void DelayUs(u32 delay_us) __attribute__((optimize("-O0")));
void DelayS(u32 delay_s) __attribute__((optimize("-O0")));

/*
** reverse string in place 
*/
void reverse(char *s);

char getNumber(int n);

namespace utils
{
void itoa(int n, char * s, int base_n);
}


 
