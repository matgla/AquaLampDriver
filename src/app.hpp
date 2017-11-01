#pragma once

#include <boost/sml.hpp>
#include <cstdio>

#include "board.hpp"
#include "logger/logger.hpp"


namespace states
{
class Init;
class DisplayInfo;
class Menu;
}

namespace events
{
class ButtonUp
{
};
class ButtonDown
{
};
class ButtonLeft
{
};
class ButtonRight
{
};
class ButtonSelect
{
};
class ButtonBack
{
};
class Update
{
};
}

class AppSm
{
  public:
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;
        // clang-format off
        return make_transition_table(
            *state<Init> / [] {printf("Display Time\n");} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonDown> / [] { printf("Show Menu\n"); } = state<Menu>,
            state<DisplayInfo> + event<ButtonLeft> / [] { printf("Show Menu\n"); } = state<Menu>,
            state<DisplayInfo> + event<ButtonRight> / [] { printf("Show Menu\n"); } = state<Menu>,
            state<DisplayInfo> + event<ButtonUp> / [] { printf("Show Menu\n"); } = state<Menu>,
            state<DisplayInfo> + event<ButtonSelect> / [] { printf("Show Menu\n"); } = state<Menu>,
            state<DisplayInfo> + event<ButtonDown> / [] { printf("Show Menu\n"); } = state<Menu>,           
            state<DisplayInfo> + event<Update> / [] { printf("Display Time\n"); } = state<DisplayInfo>,           
            state<Menu> + event<ButtonBack> / [] { printf("Display Time\n"); } = state<DisplayInfo>
        );
        // clang-format on
    }
};


class App
{
  public:
    App();

    void pressButton(const Buttons& button);
    void run();

  private:
    boost::sml::sm<AppSm> statemachine_;
    logger::Logger logger_;
};