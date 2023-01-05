cmake_minimum_required(VERSION 3.24)
project(AdventOfCode2019 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(include)

#
# Dependencies
#
include(FetchContent)
FETCHCONTENT_DECLARE(
        range-v3
        GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
        GIT_TAG a81477931a8aa2ad025c6bda0609f38e09e4d7ec
)
FETCHCONTENT_MAKEAVAILABLE(range-v3)

FetchContent_Declare(
        lexy
        GIT_REPOSITORY https://github.com/foonathan/lexy.git
        GIT_TAG        5b7095dab03041b4daf7c6c521118645491b7062
)
FetchContent_MakeAvailable(lexy)

find_package(cpr REQUIRED)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG        b7c21ec5ceeadb4951b00396fc1e4642dd347e5f
)
FetchContent_MakeAvailable(doctest)

FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG        c2ea58c7f9bb2a1da2d3d7f5b462121ac6a07f16
)
FetchContent_MakeAvailable(cli11)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        a33701196adfad74917046096bf5a2aa0ab0bb50
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        inja
        GIT_REPOSITORY https://github.com/pantor/inja.git
        GIT_TAG        2d515078c647457436556763aca8d4bf7d11d5e8
)
FetchContent_MakeAvailable(inja)
#
# Library
#
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-fconcepts HAS_CONCEPTS)

set(AOC_SOURCE
        src/aoc/remote.cpp
        src/aoc/registry.cpp
        src/aoc/runner.cpp
        )


add_library(aoclib STATIC ${AOC_SOURCE})
target_link_libraries(aoclib PUBLIC range-v3::range-v3 cpr::cpr foonathan::lexy::core foonathan::lexy::file)
target_include_directories(aoclib PRIVATE ${cpr_SOURCE_DIR}/include)
target_compile_options(aoclib PUBLIC -O3 -Wall -pedantic -Wextra -Wno-error)

if(HAS_CONCEPTS)
    target_compile_options(aoclib PUBLIC -fconcepts)
endif()

#
# CLI
#
file(
    GLOB DAYS_SOURCE
    CONFIGURE_DEPENDS
    "src/*/day*.cpp")
message(STATUS "Found days: ${DAYS_SOURCE}")

add_executable(aoc src/aoc/cli.cpp ${DAYS_SOURCE})
target_link_libraries(aoc PRIVATE aoclib CLI11::CLI11 fmt::fmt)
target_compile_definitions(aoc PRIVATE DOCTEST_CONFIG_DISABLE)
target_include_directories(aoc PRIVATE
        ${doctest_SOURCE_DIR}/doctest
        ${inja_SOURCE_DIR}/single_include
        ${inja_SOURCE_DIR}/third_party/include
        ${cli11_SOURCE_DIR}/include)

if(AOC_BUILD_TESTS)
    message(STATUS "Building tests")

    file(GLOB TESTS_SOURCE CONFIGURE_DEPENDS "tests/*.cpp")
    message(STATUS "Found tests: ${TESTS_SOURCE}")

    add_executable(aoctest src/tests.cpp ${TESTS_SOURCE} ${DAYS_SOURCE})
    target_link_libraries(aoctest PRIVATE aoclib doctest::doctest)
    target_include_directories(aoctest PRIVATE ${doctest_SOURCE_DIR}/doctest)
    add_test(aoctest aoctest)
endif()