#include "hal/utils/assert.hpp"
#include "logger/logger.hpp"


namespace hal
{
namespace utils
{

void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg)
{
    logger::Logger logger("HAL");
    logger.error() << "Assertion failed (" << expr << ") in " << file << ":" << line << " in " << function;
    logger.error() << "Assertion message: " << msg;
#ifndef NDEBUG
    while (true)
    {
    }
#endif
}

} // namespace utils
} // namespace hal