#pragma once

#include <array>
#include <ctime>

#include "app/context.hpp"
#include "controller/channelController.hpp"
#include "logger/logger.hpp"

namespace controller
{

template<const std::size_t NumberOfChannels = 1>
class SunlightController
{
public:
    SunlightController(app::Context& context) 
    : context_(context), logger_("SunlightController")
{
    // TODO: boundary check
    int i = 0;
    for (auto& channel : context_.getAllChannels())
    {
        channels_[i++].setChannel(&channel);
    }
}


    void fastSunrise(std::time_t startTime)
{
    logger_.info() << "Performing fast sunrise";
    for (auto& channel : channels_)
    {
        channel.performFastSunrise(startTime);
    }
}
    void fastSunset(std::time_t startTime)
{
    logger_.info() << "Performing fast sunset";
    for (auto& channel : channels_)
    {
        channel.performFastSunset(startTime);
    }
}
    void run(std::time_t currentTime)
{
    for (auto& channel : channels_)
    {
        channel.run(currentTime);
    }
}
    ChannelController& master()
{
    return channels_[0];
}
  
    const ChannelController& master() const
{
    return channels_[0];
}
private:
    logger::Logger logger_;
    
    app::Context& context_;
    std::array<ChannelController, NumberOfChannels> channels_;
};

} // namespace controller
