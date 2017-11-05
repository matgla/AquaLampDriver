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
            state<ChannelSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 1);},
            state<TimeSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 2);},
            state<GeneralSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 3);},
            state<EffectSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 4);},
            state<About> + on_entry<_> / [](Context& context){DisplayMenu(context, 5);},
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

    static void DisplayMenu(Context& context, int selection)
    {
        using namespace drivers::lcd;
        auto& display = context.display;
        display.clear(Colors::OFF);

        if (selection == 1)
        {
            display.print("-> ");
        }
        else
        {
            display.print("   ");
        }
        display.print("1.Channel\n");
        if (selection == 2)
        {
            display.print("-> ");
        }
        else
        {
            display.print("   ");
        }
        display.print("2.Time\n");
        if (selection == 3)
        {
            display.print("-> ");
        }
        else
        {
            display.print("   ");
        }
        display.print("3.General\n");
        if (selection == 4)
        {
            display.print("-> ");
        }
        else
        {
            display.print("   ");
        }
        display.print("4.Effect\n");
        // if (selection == 5)
        // {
        //     display.print("-> ");
        // }
        // else
        // {
        //     display.print("   ");
        // }
        // display.print("5. About Settings\n");
    }
};

} // namespace statemachines
} // namepsace app