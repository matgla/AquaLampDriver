#pragma once

#include <boost/sml.hpp>
#include <cstdio>
#include <cstring>

#include "bsp/board.hpp"
#include "logger/logger.hpp"


namespace states
{
class Init;
class DisplayInfo;
class Menu;

class ChannelSettings;
class TimeSettings;
class GeneralSettings;
class EffectSettings;
class About;
}

namespace events
{
struct ButtonUp
{
};
struct ButtonDown
{
};
struct ButtonLeft
{
};
struct ButtonRight
{
};
struct ButtonSelect
{
};
struct ButtonBack
{
};
struct Update
{
};
}

void printfMenu(int selected);

struct ChannelSetting
{
    ChannelSetting(bsp::Board& board)
        : board_(board), index(0)
    {
        memset(power, 0, sizeof(power) * sizeof(u8));
    }
    bsp::Board& board_;
    int index;
    u8 power[20];
};

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

struct MenuSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;

        // clang-format off
        // class ChannelSettings;
        // class TimeSettings;
        // class GeneralSettings;
        // class EffectSettings;
        // class About;
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
        
        // state<ChannelSettingsSm> + event<ButtonBack> = state<Init>
        
        // state<About> + event<ButtonBack> = X,
        // state<EffectSettings> + event<ButtonBack> = X,
        // state<GeneralSettings> + event<ButtonBack> = X,
        // state<TimeSettings> + event<ButtonBack> = X,
        // state<ChannelSettings> + event<ButtonBack> = X
    );
        // clang-format on
    }
};

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


class App
{
  public:
    App(bsp::Board& board);

    void run();


  private:
    void update();

    ChannelSetting channelSettings_;
    boost::sml::sm<AppSm> statemachine_;
    logger::Logger logger_;
    bsp::Board& board_;
};