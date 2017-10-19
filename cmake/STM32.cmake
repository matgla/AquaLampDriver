include(cmake/STM32-Toolchain.cmake)

if(NOT DEFINED STM32_FAMILY)
    message(FATAL_ERROR "STM32_FAMILY must be set to one of the following values: STM32F10x, STM32F2xx, STM32F4xx")
else(NOT DEFINED STM32_FAMILY)
    if(${STM32_FAMILY} STREQUAL "STM32F10x")
        set(STM32_PACKAGE_NAME ${STM32_FAMILY})
    elseif(${STM32_FAMILY} STREQUAL "STM32F2xx")
        set(STM32_PACKAGE_NAME ${STM32_FAMILY})
    elseif(${STM32_FAMILY} STREQUAL "STM32F4xx")
        set(STM32_PACKAGE_NAME ${STM32_FAMILY})
    else()
        message(FATAL_ERROR "STM32_FAMILY must be set to one of the following values: STM32F10x, STM32F2xx, STM32F4xx")
    endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(${STM32_PACKAGE_NAME} REQUIRED)
find_package(STLinkUtility)

