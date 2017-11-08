#pragma once

#include "utils/types.hpp"
#include <cstring>
#include <stdint.h>

/*
** reverse string in place 
*/
void reverse(char* s);

char getNumber(int n);
volatile u64 getTicks();

namespace utils
{
int itoa(int n, char* s, int base_n = 10);
}
