set(COMMON_BSP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/bsp")

set(bsp_common_sources
    ${COMMON_BSP_SOURCE_DIR}/board.cpp
)

set(bsp_common_includes
    ${COMMON_BSP_SOURCE_DIR}/board.hpp
    ${COMMON_BSP_SOURCE_DIR}/button.hpp
    ${COMMON_BSP_SOURCE_DIR}/led.hpp
)