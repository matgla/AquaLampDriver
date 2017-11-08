// #include "app/app.hpp"
// #include "bsp/board.hpp"
#include "logger/logger.hpp"

// #include "drivers/lcd/display.hpp"

int main()
{
    logger::Logger logger("Test");
    logger.info() << "Hejze";
    logger.warning() << "ho";
    logger.error() << "Dziala " << 10000;
    // bsp::BoardInit();
    // bsp::Board board;
    // drivers::lcd::Display display;
    // display.clear(drivers::lcd::Colors::OFF);
    // app::App app(display, board);
    // app.start();
    // app.run();
}
