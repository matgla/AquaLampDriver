#pragma once

#define HAL_ASSERT_MSG(expr, msg) ((expr) ? (void)0 : hal::utils::assertFailed(#expr, __FILE__, __LINE__, __FUNCTION__, msg))

namespace hal
{
namespace utils
{

void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg);

} // namespace utils
} // namespace hal