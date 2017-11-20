#pragma once

#include <boost/sml.hpp>
#include <cstdio>
#include <cstring>

#include "app/context.hpp"
#include "app/statemachines/appSm.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"
#include "drivers/devices/ds18b20.hpp"
#include "logger/logger.hpp"
#include "timer/manager.hpp"


namespace app
{

class App
{
public:
    App(display::Display& driver, bsp::Board& board);

    void run();
    void start();

private:
    void update();

    logger::Logger logger_;
    display::Display& display_;
    bsp::Board& board_;
    Context context_;
    boost::sml::sm<statemachines::AppSm> statemachine_;
    drivers::devices::Ds18b20<2> termometers_;
};

} // namespace app
