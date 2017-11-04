#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/statemachines/events.hpp"
#include "app/statemachines/menuSm.hpp"
#include "app/statemachines/states.hpp"

namespace app
{
namespace statemachines
{

struct AppSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;
        // clang-format off
        return make_transition_table(
            *state<Init> / [] {printf("Display Time\n");} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonDown> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonLeft> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonRight> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonUp> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonSelect> = state<MenuSm>,
            state<DisplayInfo> + event<Update> / [] { printf("Display Time\n"); } = state<DisplayInfo>,           
            state<MenuSm> + event<ButtonBack> / [] { printf("Display Time\n"); } = state<DisplayInfo>
        );
        // clang-format on
    }
};

} // namespace statemachines
} // namepsace app