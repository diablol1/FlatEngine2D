project(core)

set(SOURCE_FILES ecs/Component.hpp ecs/Destroyable.hpp ecs/Destroyable.cpp ecs/Entity.hpp ecs/Entity.cpp Game.cpp Game.hpp components/Sprite.hpp components/Sprite.cpp components/Transform.hpp components/Transform.cpp ecs/Serializable.hpp ecs/ComponentsCreator.cpp ecs/ComponentsCreator.hpp common/Utility.cpp common/Utility.hpp common/Logger.hpp common/Logger.cpp common/Vector2.hpp common/Vector2.cpp components/Camera.cpp components/Camera.hpp ecs/Component.cpp components/AnimationPlayer.cpp components/AnimationPlayer.hpp Animation.cpp Animation.hpp Frame.cpp Frame.hpp lib/termcolor.hpp lib/json.hpp common/Input.cpp common/Input.hpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
