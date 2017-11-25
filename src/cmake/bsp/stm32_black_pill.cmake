set(STM32_BLACK_PILL_BSP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/bsp/Stm32_Black_Pill")
set(DRIVERS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/drivers")


set(stm32_black_pill_sources
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/boardSpecific.cpp
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/button.cpp
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/led.cpp
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/spi.cpp    
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/onewire_stm32.cpp    
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/pwm_stm32.cpp    
)

set(stm32_black_pill_includes
)
