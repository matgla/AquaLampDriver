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
#include "utils.hpp"

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
            state<DisplayInfo> + event<Update> / [](Context& context){DisplayTime(context);} = state<DisplayInfo>,           
            state<MenuSm> + event<ButtonBack> / [](Context& context){DisplayTime(context);} = state<DisplayInfo>
        );
        // clang-format on
    }

    static void DisplayTime(Context& context)
    {
        context.display.clear(drivers::lcd::Colors::OFF);
        constexpr const int TimeBufferSize = 12;
        constexpr const int DateBufferSize = 10;
        char timeBuffer[TimeBufferSize];
        char dateBuffer[DateBufferSize];
        auto t = std::time(nullptr);
        struct tm* currentTime = std::localtime(&t);
        utils::formatDate(dateBuffer, DateBufferSize, currentTime);
        utils::formatTime(timeBuffer, TimeBufferSize, currentTime);
        context.display.print("    ");
        context.display.print(dateBuffer);
        context.display.print("    \n");
        context.display.print(timeBuffer);
    }
};

} // namespace statemachines
} // namepsace app