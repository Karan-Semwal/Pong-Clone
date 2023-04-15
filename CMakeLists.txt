cmake_minimum_required(VERSION 3.10)

project(Pong-Clone)

add_subdirectory(dependencies/SFML)

add_executable(Pong-Clone main.cpp Game.cpp)

target_link_libraries(Pong-Clone sfml-graphics sfml-window sfml-system)