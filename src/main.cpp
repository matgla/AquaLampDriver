#include "app/app.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"
#include "display/font.hpp"


// TODO: remove this ugly preprocessor


#ifdef PCD8544_DISPLAY
#include "drivers/lcd/pcd8544/displayPcd8544.hpp"
#elif SFML_DISPLAY
#include "drivers/lcd/sfml/displaySfml.hpp"
#endif

int main()
{
    bsp::BoardInit();
    bsp::Board board;

#ifdef PCD8544_DISPLAY
    drivers::lcd::DisplayPcd8544 lcdDriver(board);
#elif SFML_DISPLAY
    drivers::lcd::DisplaySfml lcdDriver;
#endif
    display::Display display(board, lcdDriver, display::font_5x7);
    display.clear(display::Colors::OFF);
    display.print("Hej\nho\n");
    display.print("Wyswietlacz dziala\n");
    display.print("lalalal\n");
    app::App app(display, board);
    app.start();
    app.run();

    return 0;
}
