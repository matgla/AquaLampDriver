#include "controller/sunlightController.hpp"

namespace controller
{

SunlightController::SunlightController()
    : state_(SunlightController::State::Off)
{
}

const SunlightController::State SunlightController::state() const
{
    return state_;
}

void SunlightController::run(std::time_t currentTime)
{
    switch (state_)
    {
        case State::Off
        {

        } break;
    }
}


} // namespace controller