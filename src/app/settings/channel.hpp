#pragma once

#include <type_traits>

#include "app/settings/timeEventSettings.hpp"
#include "utils/constants.hpp"
#include "utils/types.hpp"

namespace app
{
namespace settings
{

struct Channel
{
    u8 dayPower() const;
    u8& dayPower();
    void dayPower(u8 power);
    
    u8 nightPower() const;
    u8& nightPower();
    void nightPower(u8 power);
    
    u8 currentPower() const;
    u8& currentPower();
    void currentPower(u8 power);
    
    void setSunriseTime(u8 hour, u8 minute, u8 second, std::time_t length);
    void setSunsetTime(u8 hour, u8 minute, u8 second, std::time_t length);
    
    const TimeEventSettings& getSunriseTime() const;
    TimeEventSettings& getSunriseTime();

    const TimeEventSettings& getSunsetTime() const;
    TimeEventSettings& getSunsetTime();
    
    std::size_t fastOperationLength() const;
    std::size_t& fastOperationLength();
    void fastOperationLength(std::size_t length);
    

private:
    u8 dayPower_;
    u8 nightPower_;
    u8 currentPower_;
    
    
    
    std::size_t fastOperationLength_;

    TimeEventSettings sunriseTime_;
    TimeEventSettings sunsetTime_;
};

static_assert(std::is_pod<Channel>::value, "Channel must be POD type");

} // namespace settings
} // namespace app
