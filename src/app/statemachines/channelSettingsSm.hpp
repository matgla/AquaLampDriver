#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/context.hpp"
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
            [](Context& context) 
            {  
                printf("\e[2JChannel configuration:\n");
                printf("CH %2d : %3d %%\n", context.channelSetting.index, context.channelSetting.power[context.channelSetting.index]); 
            },
            state<ChannelSettings> + event<ButtonDown> / 
            [](Context& context) 
            {
                ++context.channelSetting.index;
            } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonUp> / 
            [](Context& context) 
            {
                --context.channelSetting.index;
            } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonLeft> / 
            [](Context& context) 
            {
                if (context.channelSetting.board_.leftButton.isLongPressed())
                {
                    context.channelSetting.power[context.channelSetting.index] -= 5;
                }
                else
                {
                    --context.channelSetting.power[context.channelSetting.index];                    
                }
            } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonRight> / 
            [](Context& context)
            {
                if (context.channelSetting.board_.rightButton.isLongPressed())
                {
                    context.channelSetting.power[context.channelSetting.index] += 5;
                }
                else
                {
                    ++context.channelSetting.power[context.channelSetting.index];                    
                }
            } = state<ChannelSettings>
        );
            // clang-format off
        }
};

} // namespace statemachines
} // namepsace app