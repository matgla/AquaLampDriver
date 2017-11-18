enable_testing()

include(../cmake/e2e_sources.cmake)
include(../cmake/production_sources.cmake)
include(../cmake/bsp_testing_sources.cmake)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test/UT)

include_directories(SYSTEM ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(SYSTEM ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(target_libs ${target_libs} ${Boost_LIBRARIES} gsl)

add_executable(AquaLampServerE2ETests
    ${e2e_sources}
    ${production_sources}
    ${bsp_sources}
)

set(testing_libs ${testing_libs} gmock gtest)

target_link_libraries(AquaLampServerE2ETests ${target_libs} ${common_libs} ${testing_libs})
