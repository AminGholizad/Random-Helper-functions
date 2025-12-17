cmake_minimum_required(VERSION 3.15)
project(Random-Helper LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Build library (INTERFACE for header-only, STATIC if src present)
file(GLOB LIB_SRC CONFIGURE_DEPENDS src/*.cpp)

if (LIB_SRC)
    add_library(Random-Helper STATIC ${LIB_SRC})

    # These settings are only valid for a STATIC target
    target_include_directories(Random-Helper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) # Changed PUBLIC to PRIVATE for the BUILD_INTERFACE part of the original line

    target_compile_options(Random-Helper PRIVATE
        -Wall -Wextra -Werror
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Wpedantic -Wconversion -Wsign-conversion
        -Wnull-dereference -Wdouble-promotion -Wformat=2
        -Wimplicit-fallthrough
    )
    target_compile_options(Random-Helper PRIVATE
        \$<$<CONFIG:Debug>:-O0>
        \$<$<CONFIG:Release>:-O3 -DNDEBUG>
        \$<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
        \$<$<CONFIG:RelWithDebInfo>:-O2 -DNDEBUG>
    )
    target_link_options(Random-Helper PRIVATE
        \$<$<CONFIG:Debug>:-g>
        \$<$<CONFIG:RelWithDebInfo>:-g>
    )
else()
    add_library(Random-Helper INTERFACE)
endif()

set_target_properties(Random-Helper PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(Random-Helper INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
add_library(Random-Helper::Random-Helper ALIAS Random-Helper)
option(Random-Helper_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})
if (Random-Helper_BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.11.0
    )

    FetchContent_MakeAvailable(Catch2)
    enable_testing()
    add_executable(Random-HelperTests tests/test_main.cpp)
    target_include_directories(Random-HelperTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(Random-HelperTests PRIVATE Catch2::Catch2WithMain Random-Helper)

    # Apply the same strict warnings
    target_compile_options(Random-HelperTests PRIVATE
        -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2
        -Wimplicit-fallthrough
    )

    target_compile_options(Random-HelperTests PRIVATE
        \$<$<CONFIG:Debug>:-O0>
        \$<$<CONFIG:Release>:-O3 -DNDEBUG>
        \$<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
        \$<$<CONFIG:RelWithDebInfo>:-O2 -DNDEBUG>
    )

    target_link_options(Random-HelperTests PRIVATE
        \$<$<CONFIG:Debug>:-g>
        \$<$<CONFIG:RelWithDebInfo>:-g>
    )
    include(Catch)
    catch_discover_tests(Random-HelperTests)
endif()
