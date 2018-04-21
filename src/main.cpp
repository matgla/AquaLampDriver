#include "app/app.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"
#include "display/font.hpp"

extern "C"
{
    #include <hdlc/minihdlc.h>
}

// TODO: remove this ugly preprocessor

#ifdef PCD8544_DISPLAY
#include "drivers/lcd/pcd8544/displayPcd8544.hpp"
#elif SFML_DISPLAY
#include "drivers/lcd/sfml/displaySfml.hpp"
#endif

void read(const uint8_t* framebuffer, uint16_t framelength) {}
void write(uint8_t d) {}

int main()
{
    minihdlc_init(write, read);
    uint8_t data[20];
    minihdlc_send_frame(data, 20);
    minihdlc_char_receiver(2);
    bsp::BoardInit();
    bsp::Board board;

#ifdef PCD8544_DISPLAY
    drivers::lcd::DisplayPcd8544 lcdDriver(board);
#elif SFML_DISPLAY
    drivers::lcd::DisplaySfml lcdDriver;
#endif
    display::Display display(board, lcdDriver, display::font_5x7);

    app::App app(display, board);
    app.start();
    app.run();


    return 0;
}
