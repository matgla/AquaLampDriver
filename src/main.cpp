#include "app.hpp"
#include "bsp/board.hpp"
#include "logger/logger.hpp"

int main()
{
    bsp::BoardInit();
    bsp::Board board;
    App app(board);
    app.run();
}
