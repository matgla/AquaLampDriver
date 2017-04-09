################################################################################
# --- STM32-CodeSourcery-CMake project example ---
# This project is intended as an example/template showing how to use CMake to
# build C/C++ source code for the STM32 using the CodeSourcery G++ Lite
# toolchain.
#
# Copyright ISORG 2012 (www.isorg.fr)
################################################################################

cmake_minimum_required(VERSION 2.8)

# Turn ON/OFF verbose output
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(ARM_TOOLCHAIN, $ENV{ARM_TOOLCHAIN})

option(BUILD_TESTS OFF "Build all tests")
option(BUILD_TARGET OFF "Build target")

if (BUILD_TARGET)
	message("Build target")
    # Add the 'Modules' folder to the search path for FindXXX.cmake files
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

    #
    # Setup STM32 variables
    #
    set(STM32_FAMILY "STM32F4xx") 	# Support "STM32F10x", "STM32F2xx", "STM32F4xx"
    include(CMake/STM32.cmake)
endif (BUILD_TARGET)

project(msos C CXX ASM)

if (ASAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif (ASAN)

if (LSAN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=leak")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif (LSAN)

if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    message("build debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -os")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -os")
endif(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")

include_directories(libs/include)

if (BUILD_TARGET)

    include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${STM32_INCLUDE_DIRS}
        )

    #add_definitions(
    #    -DUSE_STDPERIPH_DRIVER
    #    -DSTM32F4XX
    #    )

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx")

    if(DEBUG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -d -DUSE_FULL_ASSERT")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -d -DUSE_FULL_ASSERT")
    endif (DEBUG)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/lkr/stm32f407vg_flash.ld --specs=nano.specs")

    file(GLOB_RECURSE PROD_SOURCES "src/*.c" "src/*.cpp" "src/*.h" "src/*.hpp" "src/*.S")

    message("${PROD_SOURCES}")

    add_library(stm32lib
                ${STM32_SOURCES}
                ${STM32_STARTUP_SOURCE})

    add_executable(msos.elf
                ${PROD_SOURCES})

    target_link_libraries(msos.elf stm32lib ${STM32_LIBRARIES})

    add_custom_command(TARGET  POST_BUILD msos.elf
        COMMAND ${ARM_TOOLCHAIN}/bin/arm-none-eabi-size --format=berkeley "msos.elf")

    add_custom_target(msos.hex DEPENDS msos.elf COMMAND ${CMAKE_OBJCOPY} -Oihex msos.elf msos.hex)
    add_custom_target(msos.bin DEPENDS msos.elf COMMAND ${CMAKE_OBJCOPY} -Obinary msos.elf msos.bin)

    # If STM32 ST-Link Utility is found, add a make target to program the chip
    if(DEFINED STM32_STLINK_CLI_EXECUTABLE)
        # -c SWD UR : SWD communication protocol, Under Reset
        # -Q : quiet mode, no progress bar
        # -V : Verifies that the programming operation was performed successfully.
        # -P : program file (.hex)
        set(STLINK_CMD ${STM32_STLINK_CLI_EXECUTABLE} -c SWD UR -P ${CMAKE_BINARY_DIR}/msos.hex)
        add_custom_target(program-flash DEPENDS msos.hex COMMAND ${STLINK_CMD})
    endif()
endif (BUILD_TARGET)

if (BUILD_TESTS)
    add_definitions(-DBUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)
