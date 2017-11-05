#pragma once

#include <cstdio>
#include <ctime>
#include <functional>

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/helpers.hpp"
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
            *state<Init> / [](Context& context){DisplayTime(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonDown> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonLeft> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonRight> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonUp> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonSelect> = state<MenuSm>,
            state<DisplayInfo> + event<Update> / [](Context& context){DisplayTime(context);}  = state<DisplayInfo>,           
            state<MenuSm> + event<ButtonBack> / [](Context& context){DisplayTime(context);}  = state<DisplayInfo>
        );
        // clang-format on
    }

    static void DisplayTime(Context& context)
    {
        context.display.clear(drivers::lcd::Colors::OFF);
        const int TIME_BUFFER_SIZE = 30;
        char buffer[TIME_BUFFER_SIZE];
        auto t = std::time(nullptr);
        struct tm* currentTime = std::localtime(&t);
        std::strftime(static_cast<char*>(buffer), TIME_BUFFER_SIZE, "%d/%m/%y %H:%M:%S\0", currentTime);
        context.display.print(buffer);
    }
};

} // namespace statemachines
} // namepsace app