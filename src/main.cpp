#include "app/app.hpp"
#include "bsp/board.hpp"
#include "logger/logger.hpp"

#include "bsp/x86/window.hpp"

int main()
{
    bsp::BoardInit();
    bsp::Board board;
    app::App app(board);
    app.run();
}
