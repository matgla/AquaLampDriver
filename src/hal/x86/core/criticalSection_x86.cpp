#include "hal/core/criticalSection.hpp"

#include <mutex>

#include <iostream>
namespace hal
{
namespace core
{

std::mutex globalLock;
std::mutex lockedMutex;
bool locked = false;
void startCriticalSection()
{
    std::lock_guard<std::mutex> lock(lockedMutex);
    std::cerr << "lock" << std::endl;
    globalLock.lock();
    locked = true;
}

void stopCriticalSection()
{
    std::lock_guard<std::mutex> lock(lockedMutex);

    if (locked)
    {
        locked = false;
        std::cerr << "unlock" << std::endl;
        globalLock.unlock();
    }
}

} // namespace core
} // namespace hal
