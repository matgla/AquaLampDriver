set(STM32_BLACK_PILL_BSP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/bsp/Stm32_Black_Pill")
set(DRIVERS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/drivers")


set(stm32_black_pill_sources
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/boardSpecific.cpp
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/button.cpp
    ${STM32_BLACK_PILL_BSP_SOURCE_DIR}/led.cpp
    ${DRIVERS_SRC_DIR}/lcd/pcd8544/display.cpp
    
)

set(stm32_black_pill_includes
)