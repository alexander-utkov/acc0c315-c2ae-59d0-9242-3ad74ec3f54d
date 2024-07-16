cmake_minimum_required(VERSION 3.5)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG b50e685db996c167e6c831dcef582aba6e14276a
) # 11.0.1
FetchContent_MakeAvailable(fmt)

project(main)
set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(main ${SOURCES})
target_link_libraries(main fmt::fmt)
