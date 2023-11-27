cmake_minimum_required(VERSION 3.23)
project(Chip8)

set(CMAKE_CXX_STANDARD 14)

# Bring in GoogleTest
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929  # release-1.11.0
        )
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
include_directories(${googletest_SOURCE_DIR}/googletest/include)

# Bring in SDL
FetchContent_Declare(sdl
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG 15ead9a40d09a1eb9972215cceac2bf29c9b77f6
        )
FetchContent_GetProperties(sdl)
if(NOT sdl_POPULATED)
    FetchContent_Populate(sdl)
    add_subdirectory(${sdl_SOURCE_DIR} ${sdl_BINARY_DIR})
endif()
include_directories(${sdl_SOURCE_DIR}/sdl/include)
add_executable(Chip8 main.cpp)
target_include_directories(Chip8 PRIVATE ${sdl_SOURCE_DIR}/include)



