#include "hal/core/criticalSection.hpp"

#include <mutex>

namespace hal
{
namespace core
{

static std::mutex globalLock;

void startCriticalSection()
{
    globalLock.lock();
}

void stopCriticalSection()
{
    globalLock.unlock();
}

} // namespace core
} // namespace hal