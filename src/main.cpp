#include "app/app.hpp"
#include "bsp/board.hpp"

#include "drivers/lcd/display.hpp"

int main()
{
    bsp::BoardInit();
    bsp::Board board;
    drivers::lcd::Display display;
    display.clear(drivers::lcd::Colors::OFF);
    app::App app(display, board);
    app.start();
    app.run();
}
