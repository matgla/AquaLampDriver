#include "app.hpp"
#include "bsp/board.hpp"

int main(void)
{
    bsp::BoardInit();
    Board board;
    App app(board);
    app.run();
}
