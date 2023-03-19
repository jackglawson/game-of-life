cmake_minimum_required(VERSION 3.24)
project(game_of_life)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
add_executable(game_of_life main.cpp display.cpp display.h world.cpp world.h gif.h)
target_link_libraries(game_of_life PRIVATE SDL2::SDL2)
