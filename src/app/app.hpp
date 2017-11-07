#pragma once

#include <boost/sml.hpp>
#include <cstdio>
#include <cstring>

#include "app/context.hpp"
#include "app/statemachines/appSm.hpp"
#include "bsp/board.hpp"
#include "logger/logger.hpp"
#include "timer/manager.hpp"

#include "drivers/lcd/display.hpp"

namespace app
{

class App
{
public:
    App(drivers::lcd::Display& display, bsp::Board& board);

    void run();
    void start();

private:
    void update();

    Context context_;
    logger::Logger logger_;
    drivers::lcd::Display& display_;
    bsp::Board& board_;
    boost::sml::sm<statemachines::AppSm> statemachine_;
};

} // namespace app
