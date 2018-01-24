cmake_minimum_required(VERSION 3.2)
project(Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(core)
add_subdirectory(core)

add_executable(${PROJECT_NAME} game/main.cpp)
target_link_libraries(${PROJECT_NAME} core)
