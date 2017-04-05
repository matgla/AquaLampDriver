#include <sstream>

#include "stringify.hpp"

namespace std
{
std::string to_string(GPIO_TypeDef* gpio)
{
    std::stringstream ss;
    if (nullptr == gpio)
    {
        ss << "GPIO_TypeDef* is null";
    }
    else
    {
        ss << "GPIO_TypeDef*(" << std::hex << gpio << ")"
           << std::to_string(gpio->MODER) << std::to_string(gpio->OTYPER)
           << std::to_string(gpio->OSPEEDR) << std::to_string(gpio->PUPDR)
           << std::to_string(gpio->IDR) << std::to_string(gpio->ODR)
           << std::to_string(gpio->BSRRL) << std::to_string(gpio->BSRRH)
           << std::to_string(gpio->LCKR) << "[" << std::to_string(gpio->AFR[0])
           << std::to_string(gpio->AFR[1]) << "]";
    }

    return ss.str();
}

std::string to_string(GPIO_InitTypeDef* gpio)
{
    std::stringstream ss;
    ss << "GPIO_InitTypeDef*(" << std::hex << gpio << ")"
       << std::to_string(gpio->GPIO_Pin) << std::to_string(gpio->GPIO_Mode)
       << std::to_string(gpio->GPIO_Speed) << std::to_string(gpio->GPIO_OType)
       << std::to_string(gpio->GPIO_PuPd);
    return ss.str();
}

std::string to_string(NVIC_InitTypeDef* nvic)
{
    std::stringstream ss;
    ss << "NVIC_InitTypeDef*(" << std::hex << nvic << ")"
       << std::to_string(nvic->NVIC_IRQChannel)
       << std::to_string(nvic->NVIC_IRQChannelPreemptionPriority)
       << std::to_string(nvic->NVIC_IRQChannelSubPriority)
       << std::to_string(nvic->NVIC_IRQChannelCmd);
    return ss.str();
}

std::string to_string(USART_TypeDef* usart)
{
    std::stringstream ss;
    ss << "USART_TypeDef*(" << std::hex << usart << ")"
       << std::to_string(usart->SR)
       << std::to_string(usart->RESERVED0)
       << std::to_string(usart->DR)
       << std::to_string(usart->RESERVED1)
       << std::to_string(usart->BRR)
       << std::to_string(usart->RESERVED2)
       << std::to_string(usart->CR1)
       << std::to_string(usart->RESERVED3)
       << std::to_string(usart->CR2)
       << std::to_string(usart->RESERVED4)
       << std::to_string(usart->CR3)
       << std::to_string(usart->RESERVED5)
       << std::to_string(usart->GTPR)
       << std::to_string(usart->RESERVED6);

    return ss.str();
}
}
