#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/channelSetting.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"

namespace app
{
namespace statemachines
{

struct ChannelSettingsSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;
        // clang-format off
        return make_transition_table(
            *state<Init> / [] { printf("\e[2JChannel configuration:\n"); } = state<ChannelSettings>,
            state<ChannelSettings> + on_entry<_> / 
            [](ChannelSetting& setting) 
            {  
                printf("\e[2JChannel configuration:\n");
                printf("CH %2d : %3d %%\n", setting.index, setting.power[setting.index]); 
            },
            state<ChannelSettings> + event<ButtonDown> / 
            [](ChannelSetting& setting) 
            {
                ++setting.index;
            } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonUp> / 
            [](ChannelSetting& setting) 
            {
                --setting.index;
            } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonLeft> / 
            [](ChannelSetting& setting) 
            {
                if (setting.board_.leftButton.isLongPressed())
                {
                    setting.power[setting.index] -= 5;
                }
                else
                {
                    --setting.power[setting.index];                    
                }
            } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonRight> / 
            [](ChannelSetting& setting)
            {
                if (setting.board_.rightButton.isLongPressed())
                {
                    setting.power[setting.index] += 5;
                }
                else
                {
                    ++setting.power[setting.index];                    
                }
            } = state<ChannelSettings>
        );
            // clang-format off
        }
};

} // namespace statemachines
} // namepsace app