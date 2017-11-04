#pragma once

#include <boost/sml.hpp>
#include <cstdio>
#include <cstring>

#include "app/channelSetting.hpp"
#include "app/statemachines/appSm.hpp"
#include "bsp/board.hpp"
#include "logger/logger.hpp"

#include "drivers/lcd/display.hpp"

namespace app
{

class App
{
public:
    App(bsp::Board& board);

    void run();

private:
    void update();

    ChannelSetting channelSettings_;
    boost::sml::sm<statemachines::AppSm> statemachine_;
    logger::Logger logger_;
    bsp::Board& board_;
    drivers::lcd::Display display_;
};

} // namespace app
