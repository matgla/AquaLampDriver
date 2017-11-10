#include "app/app.hpp"
#include "bsp/board.hpp"
#include "drivers/lcd/display.hpp"

// #include <stm32f10x.h>

int main()
{
    bsp::BoardInit();
    bsp::Board board;
    drivers::lcd::Display display(board);
    display.clear(drivers::lcd::Colors::OFF);
    app::App app(display, board);
    app.start();
    app.run();
}
