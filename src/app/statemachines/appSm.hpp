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


    /* 10000
       11000
       10100
       10010
       10100
       11000
       10000

       */


    static void DisplayTime(Context& context)
    {
        context.display.clear(drivers::lcd::Colors::OFF);
        const int TIME_BUFFER_SIZE = 30;
        char buffer[TIME_BUFFER_SIZE];
        auto t = std::time(nullptr);
        struct tm* currentTime = std::localtime(&t);
        std::strftime(static_cast<char*>(buffer), TIME_BUFFER_SIZE, "   %d/%m/%y\n   %H:%M:%S\n", currentTime);
        context.display.print(buffer);
        const u8 arrow[4] =
            {
                0b11111110,
                0b01000100,
                0b00101000,
                0b00010000};
        context.display.drawImage(gsl::span<const u8>{arrow}, 4, 7);
        // char buffer[]

        // sprintf(buffer, "")

        // context.display.print(
    }

    /*
    01110
    10001
    10001
    01110
    01110
    01110
    00000
    */
};

} // namespace statemachines
} // namepsace app