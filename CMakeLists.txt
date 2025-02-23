cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(kosmos VERSION 1.0.0 LANGUAGES CXX)

add_compile_options(
"$<$<COMPILE_LANGUAGE:CXX>:-Wall;-pipe>"
)

include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:-g>"
    )
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    add_compile_options(
    "$<$<COMPILE_LANGUAGE:CXX>:-O3;-march=native>"
    )
endif()

add_executable(kosmos src/main.cpp src/math/Coords.cpp src/types/CosmicObject.cpp src/utils/game.cpp src/utils/input.cpp src/utils/tui.cpp)