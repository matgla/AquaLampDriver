#include "app.hpp"
#include "board.hpp"
#include "logger/logger.hpp"

#include "stm32f10x_gpio.h"

#include "rtc/rtc.hpp"
#include "usart.hpp"

void initializeGPIO(GPIO_TypeDef* port, u16 pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = pin;
    gpio.GPIO_Mode = mode;
    gpio.GPIO_Speed = speed;
    GPIO_Init(port, &gpio);
}
int main(void)
{
    CoreInit();
    Board board;
    App app(board);
    app.run();
}
