#include "bsp/spi.hpp"

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_spi.h>

#include "bsp/stm32f1_common/helpers.hpp"

#define RST_PIN GPIO_Pin_15
#define RST_PORT GPIOA
#define RST_RCC RCC_APB2Periph_GPIOA

#define DC_PIN GPIO_Pin_4
#define DC_PORT GPIOB
#define DC_RCC RCC_APB2Periph_GPIOB

#define CE_PIN GPIO_Pin_12
#define CE_PORT GPIOB
#define CE_RCC RCC_APB2Periph_GPIOB

namespace bsp
{

Spi::Spi()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

    bsp::Helper::configureGpio(RST_PORT, RST_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
    bsp::Helper::configureGpio(DC_PORT, DC_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
    bsp::Helper::configureGpio(CE_PORT, CE_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

    bsp::Helper::configureGpio(GPIOB, GPIO_Pin_5, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
    bsp::Helper::configureGpio(GPIOB, GPIO_Pin_3, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);

    SPI_InitTypeDef spi;
    SPI_StructInit(&spi);
    SPI_StructInit(&spi);

    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_Init(SPI1, &spi);
    SPI_Cmd(SPI1, ENABLE);
}

void Spi::resetPinHigh() const
{
    GPIO_SetBits(RST_PORT, RST_PIN);
}

void Spi::resetPinLow() const
{
    GPIO_ResetBits(RST_PORT, RST_PIN);
}

void Spi::dcPinHigh() const
{
    GPIO_SetBits(DC_PORT, DC_PIN);
}

void Spi::dcPinLow() const
{
    GPIO_ResetBits(DC_PORT, DC_PIN);
}

void Spi::cePinHigh() const
{
    GPIO_SetBits(CE_PORT, CE_PIN);
}

void Spi::cePinLow() const
{
    GPIO_ResetBits(CE_PORT, CE_PIN);
}

u8 Spi::send(const u8 byte) const
{
    // TODO: change to timeout
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
    {

    }
    SPI_I2S_SendData(SPI1, byte);

  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
  {
  }

  return SPI_I2S_ReceiveData(SPI1);
}

} // namespace bsp
