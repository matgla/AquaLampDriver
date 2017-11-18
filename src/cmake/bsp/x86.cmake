set(X86_BSP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/bsp/x86")

set(x86_bsp_sources
    ${X86_BSP_SOURCE_DIR}/boardSpecific.cpp
    ${X86_BSP_SOURCE_DIR}/button.cpp
    ${X86_BSP_SOURCE_DIR}/led.cpp
    ${X86_BSP_SOURCE_DIR}/window.cpp
    ${X86_BSP_SOURCE_DIR}/spi.cpp
    ${X86_BSP_SOURCE_DIR}/onewire_x86.cpp
)

set(x86_bsp_includes
    ${X86_BSP_SOURCE_DIR}/window.hpp
)
