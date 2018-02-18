#include "bsp/button.hpp"

#include "bsp/stm32f1_common/helpers.hpp"

#include "logger/logger.hpp"
#include <stm32f10x_adc.h>

constexpr uint16_t BOUNDARY_OFFSET         = 300;
constexpr uint16_t BUTTON_LEFT_THRESHOLD   = 2500;
constexpr uint16_t BUTTON_DOWN_THRESHOLD   = 3000;
constexpr uint16_t BUTTON_RIGHT_THRESHOLD  = 3650;
constexpr uint16_t BUTTON_SELECT_THRESHOLD = 1900;
constexpr uint16_t BUTTON_UP_THRESHOLD     = 1100;
constexpr uint16_t BUTTON_BACK_THRESHOLD   = 600;

constexpr uint32_t COUNTER_THRESHOLD = 100;

namespace bsp
{

bool wasInitialized = false;

static uint32_t buttonLeftCounter   = 0;
static uint32_t buttonDownCounter   = 0;
static uint32_t buttonRightCounter  = 0;
static uint32_t buttonSelectCounter = 0;
static uint32_t buttonUpCounter     = 0;
static uint32_t buttonBackCounter   = 0;

void init()
{
    if (!wasInitialized)
    {
        logger::Logger logger("ADC");
        GPIO_InitTypeDef gpio;
        ADC_InitTypeDef adc;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

        RCC_ADCCLKConfig(RCC_PCLK2_Div6);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

        gpio.GPIO_Pin  = GPIO_Pin_6;
        gpio.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOA, &gpio);

        ADC_StructInit(&adc);
        adc.ADC_ContinuousConvMode = ENABLE;
        adc.ADC_NbrOfChannel       = 1;
        adc.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
        ADC_Init(ADC1, &adc);

        ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_71Cycles5);
        ADC_Cmd(ADC1, ENABLE);

        ADC_ResetCalibration(ADC1);
        while (ADC_GetResetCalibrationStatus(ADC1))
            ;

        ADC_StartCalibration(ADC1);
        while (ADC_GetCalibrationStatus(ADC1))
            ;

        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        wasInitialized = true;
        logger.info() << "adc initalized";
    }
}

template <>
Button<Buttons::Left>::Button()
{
    init();
}

template <>
Button<Buttons::Right>::Button()
{
    init();
}

template <>
Button<Buttons::Up>::Button()
{
    init();
}

template <>
Button<Buttons::Down>::Button()
{
    init();
}

template <>
Button<Buttons::Back>::Button()
{
    init();
}

template <>
Button<Buttons::Select>::Button()
{
    init();
}

template <>
bool Button<Buttons::Left>::isPinPressed()
{
    // logger::Logger logger("ADC");
    uint16_t adc = ADC_GetConversionValue(ADC1);
    // logger.info() << adc;
    if (adc > BUTTON_LEFT_THRESHOLD - BOUNDARY_OFFSET && adc < BUTTON_LEFT_THRESHOLD + BOUNDARY_OFFSET)
    {
        ++buttonLeftCounter;
    }
    else
    {
        buttonLeftCounter = 0;
    }

    if (buttonLeftCounter > COUNTER_THRESHOLD)
    {
        return true;
    }

    return false;
}

template <>
bool Button<Buttons::Down>::isPinPressed()
{
    uint16_t adc = ADC_GetConversionValue(ADC1);
    if (adc > BUTTON_DOWN_THRESHOLD - BOUNDARY_OFFSET && adc < BUTTON_DOWN_THRESHOLD + BOUNDARY_OFFSET)
    {
        ++buttonDownCounter;
    }
    else
    {
        buttonDownCounter = 0;
    }

    if (buttonDownCounter > COUNTER_THRESHOLD)
    {
        return true;
    }

    return false;
}

template <>
bool Button<Buttons::Right>::isPinPressed()
{
    uint16_t adc = ADC_GetConversionValue(ADC1);
    if (adc > BUTTON_RIGHT_THRESHOLD - BOUNDARY_OFFSET && adc < BUTTON_RIGHT_THRESHOLD + BOUNDARY_OFFSET)
    {
        ++buttonRightCounter;
    }
    else
    {
        buttonRightCounter = 0;
    }

    if (buttonRightCounter > COUNTER_THRESHOLD)
    {
        return true;
    }

    return false;
}

template <>
bool Button<Buttons::Select>::isPinPressed()
{
    uint16_t adc = ADC_GetConversionValue(ADC1);
    if (adc > BUTTON_SELECT_THRESHOLD - BOUNDARY_OFFSET && adc < BUTTON_SELECT_THRESHOLD + BOUNDARY_OFFSET)
    {
        ++buttonSelectCounter;
    }
    else
    {
        buttonSelectCounter = 0;
    }

    if (buttonSelectCounter > COUNTER_THRESHOLD)
    {
        return true;
    }

    return false;
}

template <>
bool Button<Buttons::Up>::isPinPressed()
{
    uint16_t adc = ADC_GetConversionValue(ADC1);
    if (adc > BUTTON_UP_THRESHOLD - BOUNDARY_OFFSET && adc < BUTTON_UP_THRESHOLD + BOUNDARY_OFFSET)
    {
        ++buttonUpCounter;
    }
    else
    {
        buttonUpCounter = 0;
    }

    if (buttonUpCounter > COUNTER_THRESHOLD)
    {
        return true;
    }

    return false;
}

template <>
bool Button<Buttons::Back>::isPinPressed()
{
    uint16_t adc = ADC_GetConversionValue(ADC1);
    if (adc > BUTTON_BACK_THRESHOLD - BOUNDARY_OFFSET && adc < BUTTON_BACK_THRESHOLD + BOUNDARY_OFFSET)
    {
        ++buttonBackCounter;
    }
    else
    {
        buttonBackCounter = 0;
    }

    if (buttonBackCounter > COUNTER_THRESHOLD)
    {
        return true;
    }

    return false;
}

} // namespace bsp
