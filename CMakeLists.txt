cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)

project(kosmos VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "-Wall -pipe -march=native")

include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

add_executable(kosmos src/main.cpp src/math/Coords.cpp src/types/CosmicObject.cpp src/utils/game.cpp src/utils/input.cpp src/utils/tui.cpp)

include(CTest)
enable_testing()