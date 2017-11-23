#include "app/app.hpp"

#include <cmath>

#include "app/statemachines/events.hpp"
#include "bsp/board.hpp"
#include "hal/time/rtc.hpp"
#include "logger/logger.hpp"


namespace app
{
App::App(display::Display& display, bsp::Board& board)
    : logger_("App"),
      display_(display),
      board_(board),
      context_(board, display, logger_),
      statemachine_(context_),
      termometers_(board)
{
}

void App::start()
{
    display_.backlightOff();
    logger_.info() << "Startup";
    hal::time::Rtc::get().setSecondsHandler([this] {
        this->update();
    });

    board_.led.on();
    board_.registers.startupDone();

    logger_.info() << "Started";
}

void App::update()
{
    display_.backlightOn();

    statemachine_.process_event(statemachines::events::Update{});
}

void App::run()
{
    using namespace statemachines;
    timerManager_.setInterval(1000, [this]() {
        logger_.info() << "Interval fire";

        termometers_.measureTemperature();

        float temperature = termometers_.readTemperature(0);

        char buffer[40];
        sprintf(buffer, "Temperature 1: %f", temperature);
        logger_.info() << buffer;
        auto conv = utils::floatToInts(temperature, 4);
        logger_.info() << "Temperature 1: " << conv.first << "." << conv.second << "   conv !";

        temperature = termometers_.readTemperature(1);
        sprintf(buffer, "Temperature 2: %f", temperature);
        logger_.info() << buffer;
        conv = utils::floatToInts(temperature, 4);
        logger_.info() << "Temperature 2: " << conv.first << "." << conv.second << "   conv !";

    });

    while (!board_.exit())
    {
        if (board_.downButton.isPressed())
        {
            logger_.info() << "down";
            statemachine_.process_event(events::ButtonDown{});
        }
        if (board_.upButton.isPressed())
        {
            logger_.info() << "up";
            statemachine_.process_event(events::ButtonUp{});
        }
        if (board_.leftButton.isPressed())
        {
            logger_.info() << "left";

            statemachine_.process_event(events::ButtonLeft{});
        }
        if (board_.rightButton.isPressed())
        {
            logger_.info() << "right";
            statemachine_.process_event(events::ButtonRight{});
        }
        if (board_.selectButton.isPressed())
        {
            logger_.info() << "select";
            statemachine_.process_event(events::ButtonSelect{});
        }
        if (board_.backButton.isPressed())
        {
            logger_.info() << "back";
            statemachine_.process_event(events::ButtonBack{});
        }

        // measure temperature

        // make actions
        board_.run();
        timerManager_.run();
    }
    hal::time::Rtc::get().stop();
}

} // namespace app
