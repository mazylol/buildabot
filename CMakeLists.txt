cmake_minimum_required(VERSION 3.27)
project(buildabot)

set(YAML_FILE_SOURCE ${CMAKE_SOURCE_DIR}/config.yaml)
set(YAML_FILE_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config.yaml)
configure_file(${YAML_FILE_SOURCE} ${YAML_FILE_DESTINATION} COPYONLY)

# enable ccache
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

include(FetchContent)

# dpp
FetchContent_Declare(dpp
        GIT_REPOSITORY https://github.com/brainboxdotcc/DPP
        GIT_TAG v10.0.29
)
FetchContent_MakeAvailable(dpp)

#yaml-cpp
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
)
FetchContent_GetProperties(yaml-cpp)
if (NOT yaml-cpp_POPULATED)
    message(STATUS "Fetching yaml-cpp...")
    FetchContent_Populate(yaml-cpp)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif ()

# fmt
FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/archive/refs/tags/10.2.1.tar.gz)
FetchContent_MakeAvailable(fmt)

add_executable(${PROJECT_NAME} src/main.cpp
        src/util/config.cpp
        src/util/config.h)
target_link_libraries(${PROJECT_NAME} dpp fmt::fmt yaml-cpp::yaml-cpp)

set(CMAKE_CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)