cmake_minimum_required(VERSION 3.2)
project(FlatEngine2D)

add_compile_options(-std=c++17)

include_directories(engine)

set(SOURCE_FILES game/main.cpp engine/ecs/Component.hpp engine/ecs/Destroyable.hpp engine/ecs/Destroyable.cpp engine/ecs/Entity.hpp engine/ecs/Entity.cpp engine/Game.cpp engine/Game.hpp engine/components/Sprite.hpp engine/components/Sprite.cpp engine/components/Transform.hpp engine/components/Transform.cpp engine/ecs/Serializable.hpp engine/ecs/ComponentsCreator.cpp engine/ecs/ComponentsCreator.hpp engine/common/utility.cpp engine/common/utility.hpp engine/common/Logger.hpp engine/common/Logger.cpp engine/components/Camera.cpp engine/components/Camera.hpp engine/ecs/Component.cpp engine/components/AnimationPlayer.cpp engine/components/AnimationPlayer.hpp engine/Animation.cpp engine/Animation.hpp engine/Frame.cpp engine/Frame.hpp)
add_executable(FlatEngine2D ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(FlatEngine2D ${SFML_LIBRARIES})
endif()
