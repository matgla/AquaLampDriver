include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

enable_testing()

file (GLOB_RECURSE SRCS src/*.c
                        src/*.cpp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT -DSTM32F40_41xxx -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT -DSTM32F40_41xxx -std=c++1y")

file (GLOB PROD_SRCS    ${PROJECT_SOURCE_DIR}/src/buffer.hpp
                        ${PROJECT_SOURCE_DIR}/src/logger.hpp
                        ${PROJECT_SOURCE_DIR}/src/logger.cpp
                        ${PROJECT_SOURCE_DIR}/src/utils.h
                        ${PROJECT_SOURCE_DIR}/src/usart.hpp
                        ${PROJECT_SOURCE_DIR}/src/usart.cpp
                        ${PROJECT_SOURCE_DIR}/src/messages.hpp
                        ${PROJECT_SOURCE_DIR}/src/messages.cpp
                        ${PROJECT_SOURCE_DIR}/src/utils.hpp
                        ${PROJECT_SOURCE_DIR}/src/utils.cpp
                        ${PROJECT_SOURCE_DIR}/src/usart_downloader.hpp
                        ${PROJECT_SOURCE_DIR}/src/usart_downloader.cpp
                        ${PROJECT_SOURCE_DIR}/src/bootloader.hpp
                        ${PROJECT_SOURCE_DIR}/src/bootloader.cpp
                        ${PROJECT_SOURCE_DIR}/src/handshake.hpp
                        ${PROJECT_SOURCE_DIR}/src/handshake.cpp
                        ${PROJECT_SOURCE_DIR}/src/deviceInfoReader.hpp
                        ${PROJECT_SOURCE_DIR}/src/deviceInfoReader.cpp
                        ${PROJECT_SOURCE_DIR}/src/types.h)
include_directories(${PROJECT_SOURCE_DIR}/src)

file (GLOB_RECURSE STUB_SRCS ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.cpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.c
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.hpp
                             ${PROJECT_SOURCE_DIR}/test/UT/hw_stub/*.h
                             ${PROJECT_SOURCE_DIR}/test/UT/mocks/*.cpp
                             ${PROJECT_SOURCE_DIR}/test/UT/mocks/*.c
                             ${PROJECT_SOURCE_DIR}/test/UT/mocks/*.hpp
                             ${PROJECT_SOURCE_DIR}/test/UT/mocks/*.h)

include_directories(hw_stub)
include_directories(mocks)

add_executable (bootloaderUTs ${SRCS} ${PROD_SRCS} ${STUB_SRCS})

target_link_libraries (bootloaderUTs gmock gtest gtest_main pthread)