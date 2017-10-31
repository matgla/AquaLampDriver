#pragma once

#include "types.hpp"
#include <cstring>
#include <stdint.h>

void delay(u32 delay_ms) __attribute__((optimize("-O0")));
void delays(u32 delay_s) __attribute__((optimize("-O0")));

/*
** reverse string in place 
*/
void reverse(char* s);

char getNumber(int n);
volatile u64 getTicks();

namespace utils
{
void itoa(int n, char* s, int base_n);
}
