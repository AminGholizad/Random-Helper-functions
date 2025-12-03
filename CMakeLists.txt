cmake_minimum_required(VERSION 3.10)
project(RandomHelper LANGUAGES CXX)

# ============================
# Header-only library
# ============================
add_library(RandomHelper INTERFACE)

target_include_directories(RandomHelper INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Require C++23 for consumers
target_compile_features(RandomHelper INTERFACE cxx_std_23)

# Create namespace-style alias
add_library(RandomHelper::RandomHelper ALIAS RandomHelper)

# ============================
# Optional tests / examples
# ============================
option(RH_BUILD_TESTS "Build tests for RandomHelper" OFF)

if(RH_BUILD_TESTS)
    enable_testing()
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    # Create test executable
    add_executable(RandomHelperTests
        tests/main.cpp
        # add more test files here
    )
    if(false)
        find_program(CLANG_TIDY_EXE clang-tidy)
        if(CLANG_TIDY_EXE)
            set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        "--extra-arg=--driver-mode=g++"
        "--extra-arg=-std=c++23"
        "--header-filter=${CMAKE_SOURCE_DIR}/.*"
    )
        else()
            message(WARNING "clang-tidy not found, CXX clang-tidy checks will not be run.")
        endif()
    endif()

    # Link test executable with your library
    target_link_libraries(RandomHelperTests PRIVATE RandomHelper::RandomHelper)

    # Apply strict compile flags ONLY to tests
    target_compile_options(RandomHelperTests PRIVATE
        -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -Wold-style-cast
        -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion
        -Wsign-conversion -Wnull-dereference -Wdouble-promotion
        -Wformat=2 -Wimplicit-fallthrough
    )
    # Optimization flags based on build type
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(RandomHelperTests PRIVATE -g -O0)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(RandomHelperTests PRIVATE -O3 -DNDEBUG)
    endif()
    # Register with CTest
    add_test(NAME RandomHelperTests COMMAND RandomHelperTests)
endif()
