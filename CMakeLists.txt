cmake_minimum_required(VERSION 3.2)
project(Platformer2D)

add_compile_options(-std=c++17)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.hpp src/GameState.hpp src/PlayState.cpp src/PlayState.hpp src/Enums.hpp src/EnumClassHash.hpp src/Player.cpp src/Player.hpp src/Level.cpp src/Level.hpp src/InfiniteBackground.cpp src/InfiniteBackground.hpp src/ECS/Entity.cpp src/ECS/Entity.hpp src/ECS/Component.hpp)
add_executable(Platformer2D ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Platformer2D ${SFML_LIBRARIES})
endif()
