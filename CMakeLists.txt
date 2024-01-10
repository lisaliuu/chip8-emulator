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

# Include project headers
include_directories(./include)

# Define the source and test files for the executables
set(SOURCE_FILES
        src/Memory.cpp
        src/Display.cpp
        src/Chip8.cpp
        src/Window.cpp
        src/Opcode.cpp
        src/EventHandler.cpp
        )
set(TEST_FILES
        tests/memoryTest.cpp
        tests/windowTest.cpp
        tests/main.cpp)

# Make the project root directory the working directory when we run
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Configure and link the Chip8 executable
add_executable(Chip8 ${SOURCE_FILES} main.cpp)
target_link_libraries(Chip8 SDL2 ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(Chip8 PRIVATE ${sdl_SOURCE_DIR}/include)

# Configure and link the testing executable
add_executable(testing ${SOURCE_FILES} ${TEST_FILES})
add_dependencies(testing gtest)
target_link_libraries(testing gtest SDL2 ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(testing PRIVATE ${sdl_SOURCE_DIR}/include)

