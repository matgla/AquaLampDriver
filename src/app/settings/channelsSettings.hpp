#pragma once

#include <type_traits>

#include <gsl/span>

#include "utils/constants.hpp"
#include "utils/types.hpp"

namespace app
{
namespace settings
{

struct ChannelsSettings
{
    u8 masterPower() const;
    u8& masterPower();
    void masterPower(u8 power);
    gsl::span<u8> powers();

private:
    u8 masterPower_;
    u8 channelPowers_[utils::NUMBER_OF_PWM_CHANNELS];
};
static_assert(std::is_pod<ChannelsSettings>::value, "ChannelsSettings must be POD type");

} // namespace settings
} // namespace app
