#pragma once

#include "utils.hpp"

namespace rtc
{
class Rtc
{
public:
  Rtc();
  static void setTime(u32 day, u32 month, u32 year, u32 hours, u32 minutes, u32 seconds);
  static u32 getTime();

private:
  void init();
};
} // namespace rtc