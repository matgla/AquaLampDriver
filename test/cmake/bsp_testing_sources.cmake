set(BSP_INTERFACE_DIR "${PROJECT_SOURCE_DIR}/src/bsp")
set(BSP_TEST_SOURCES_DIR "${PROJECT_SOURCE_DIR}/test/bsp/x86_test")

set(bsp_includes
    ${BSP_INTERFACE_DIR}/board.hpp
)

set(bsp_sources
    ${BSP_INTERFACE_DIR}/board.cpp
    ${BSP_TEST_SOURCES_DIR}/boardSpecific_x86_testing.cpp
    ${BSP_TEST_SOURCES_DIR}/button_x86_testing.cpp
    ${BSP_TEST_SOURCES_DIR}/led_x86_testing.cpp
    ${BSP_TEST_SOURCES_DIR}/onewire_x86_testing.cpp
    ${BSP_TEST_SOURCES_DIR}/spi_x86_testing.cpp

    ${bsp_includes}
)
