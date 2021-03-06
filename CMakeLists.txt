cmake_minimum_required(VERSION 3.1)

set(ARCH "X86" CACHE STRING "Target architecture (X86|ARM)")
set(ARM_TOOLCHAIN $ENV{ARM_TOOLCHAIN} CACHE STRING "Path to ARM toolchain")
set(BOARD "STM32_Black_Pill" CACHE STRING "Board name for choose board support platform")

set(BUILD_TARGET OFF CACHE STRING "Build target")
set(BUILD_TESTS  OFF CACHE STRING "Build tests")

set(ASAN_ENABLED OFF CACHE STRING "Enable address sanitizer")
set(LSAN_ENABLED OFF CACHE STRING "Enable leak sanitizer")
set(TSAN_ENABLED OFF CACHE STRING "Enable thread sanitizer")
set(USAN_ENABLED OFF CACHE STRING "Enable undefined sanitizer")
set(CLANG_TIDY   OFF CACHE STRING "Enable clang tidy")
set(CPPCHECK     OFF CACHE STRING "Enable cppcheck")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DEBUG        OFF CACHE STRING "Debug")

if (${ARCH} STREQUAL "STM32")
    message("-- Include toolchain for STM32")
    set(STM32_FAMILY "STM32F10x" CACHE STRING "STM32 version")
    include("cmake/STM32.cmake")
endif (${ARCH} STREQUAL "STM32")

project(AquaLampDriver CXX C ASM)

if (ASAN_ENABLED)
    if (${ARCH} STREQUAL "STM32")
        message(WARNING "STM32 not support undefined behaviour sanitizer")
    else (${ARCH} STREQUAL "STM32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    endif (${ARCH} STREQUAL "STM32")
endif (ASAN_ENABLED)

if (LSAN_ENABLED)
    if (${ARCH} STREQUAL "STM32")
        message(WARNING "STM32 not support undefined behaviour sanitizer")
    else (${ARCH} STREQUAL "STM32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=leak")
    endif (${ARCH} STREQUAL "STM32")
endif (LSAN_ENABLED)

if(ENABLE_USAN)
    if (${ARCH} STREQUAL "STM32")
        message(WARNING "STM32 not support undefined behaviour sanitizer")
    else (${ARCH} STREQUAL "STM32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    endif (${ARCH} STREQUAL "STM32")
endif()

set (clang_tidy_srcs "" CACHE INTERNAL "clang tidy sources")
    if (CLANG_TIDY)
    find_program(CLANG_TIDY_BIN clang-tidy-5.0)

    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy-5.0")
    endif()

    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
endif (CLANG_TIDY)

if (GCOV)
    if (${ARCH} STREQUAL "STM32")
        message(WARNING "STM32 not support coverage")
    endif (${ARCH} STREQUAL "STM32")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif (GCOV)

include_directories(libs/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (BUILD_TARGET)
    add_subdirectory(src)
endif (BUILD_TARGET)

if (BUILD_TESTS)
    message("Building Tests")
    if (NOT ${ARCH} STREQUAL "X86")
        message(FATAL_ERROR "Tests can be build only for X86")
    endif (NOT ${ARCH} STREQUAL "X86")

    add_subdirectory(test)
endif (BUILD_TESTS)


add_subdirectory(lib)

if (CLANG_TIDY)
    add_custom_target(
        clang_tidy
        COMMAND ${CLANG_TIDY_BIN} -checks=clan*,cert*,misc*,perf*,cppc*,read*,mode*,-cert-err58-cpp,-cert-dcl58-cpp,-misc-noexcept-move-constructor -header-filter="src" -p . ${clang_tidy_srcs}
        COMMENT "running clang tidy"
    )
endif (CLANG_TIDY)
