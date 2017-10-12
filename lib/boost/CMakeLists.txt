file(GLOB_RECURSE boost_sml_srcs
    "sml/include/*.hpp"
    "sml/include/*.h"
    "sml/include/*.ipp"
    )

set(SML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/boost/sml/include" CACHE STRING "path to Boost SML sources" FORCE)

add_library(sml INTERFACE)
target_sources(sml INTERFACE ${boost_sml_srcs})
target_include_directories(sml INTERFACE ${SML_INCLUDE_DIR})
message("sml sources ${SML_INCLUDE_DIR}")

file(GLOB_RECURSE beast_srcs
    "beast/include/*.hpp"
    "beast/include/*.h"
    "beast/include/*.ipp")

set(Beast_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/boost/beast/include" CACHE STRING "path to Beast sources" FORCE)

add_library(beast INTERFACE)
target_sources(beast INTERFACE ${beast_srcs})
target_include_directories(beast INTERFACE ${Beast_INCLUDE_DIR})
