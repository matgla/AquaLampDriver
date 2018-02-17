#pragma once

#include <array>
#include <ctime>

#include "app/contextInterface.hpp"
#include "controller/channelController.hpp"
#include "hal/utils/assert.hpp"
#include "logger/logger.hpp"

namespace controller
{

template <const std::size_t NumberOfChannels = 14>
class LightController
{
public:
    explicit LightController(app::IContext& context)
        : logger_("LightChannel"), context_(context)
    {
        logger_.info() << context_.getAllChannels().size();
        HAL_ASSERT_MSG(NumberOfChannels >= static_cast<std::size_t>(context_.getAllChannels().size()), "Channels not fit in controller");
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

    gsl::span<ChannelController> getChannels()
    {
        return gsl::span<ChannelController>{&channels_[1],
                                            static_cast<gsl::span<ChannelController>::index_type>(channels_.size() - 1)};
    }

    const gsl::span<const ChannelController> getChannels() const
    {
        return gsl::span<const ChannelController>{&channels_[1],
                                                  channels_.size() - 1};
    }

    void forceLight(bool forced)
    {
        for (auto& channel : channels_)
        {
            channel.forced(forced);
        }
    }

    bool isForced() const 
    {
        for (auto& channel : channels_)
        {
            if (channel.forced())
            {
                return true;
            }
        }

        return false;        
    }
private:
    logger::Logger logger_;

    app::IContext& context_;
    std::array<ChannelController, NumberOfChannels> channels_;
};

} // namespace controller
