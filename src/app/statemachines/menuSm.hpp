#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/statemachines/channelSettingsSm.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"

namespace app
{
namespace statemachines
{

struct MenuSm
{
    static void printfMenu(int selected)
    {
        printf("\e[2J");
        if (selected == 1)
        {
            printf("-> ");
        }
        else
        {
            printf("   ");
        }
        printf("1. Channel Settings\n");
        if (selected == 2)
        {
            printf("-> ");
        }
        else
        {
            printf("   ");
        }
        printf("2. Time Settings\n");
        if (selected == 3)
        {
            printf("-> ");
        }
        else
        {
            printf("   ");
        }
        printf("3. General Settings\n");
        if (selected == 4)
        {
            printf("-> ");
        }
        else
        {
            printf("   ");
        }
        printf("4. Effect Settings\n");
        if (selected == 5)
        {
            printf("-> ");
        }
        else
        {
            printf("   ");
        }
        printf("5. About Settings\n");
    }
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;

        // clang-format off
        return make_transition_table(
            *state<Init> / []{printf("\e[2JShow Menu:\n");} = state<ChannelSettings>,
            state<ChannelSettings> + on_entry<_> / []{printfMenu(1);},
            state<TimeSettings> + on_entry<_> / []{printfMenu(2);},
            state<GeneralSettings> + on_entry<_> / []{printfMenu(3);},
            state<EffectSettings> + on_entry<_> / []{printfMenu(4);},
            state<About> + on_entry<_> / []{printfMenu(5);},
            state<ChannelSettings> + event<ButtonDown> = state<TimeSettings>,
            state<TimeSettings> + event<ButtonDown> = state<GeneralSettings>,
            state<GeneralSettings> + event<ButtonDown> = state<EffectSettings>,
            state<EffectSettings> + event<ButtonDown> = state<About>,
            state<About> + event<ButtonDown> = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonUp> = state<About>,
            state<TimeSettings> + event<ButtonUp> = state<ChannelSettings>,
            state<GeneralSettings> + event<ButtonUp> = state<TimeSettings>,
            state<EffectSettings> + event<ButtonUp> = state<GeneralSettings>,
            state<About> + event<ButtonUp> = state<EffectSettings>,
            state<ChannelSettings> + event<ButtonSelect> = state<ChannelSettingsSm>,
            state<ChannelSettingsSm> + event<ButtonBack> = state<Init>
        );
        // clang-format on
    }
};

} // namespace statemachines
} // namepsace app