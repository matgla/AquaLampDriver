#pragma once

#include <ctime>

namespace controller
{

class SunlightController
{
public:
    enum class State
    {
        Off
    };

    SunlightController();

    const State state() const;
    void run(std::time_t currentTime);

private:
    State state_;
};

} // namespace controller
