cmake_minimum_required(VERSION 4.1)
project(maziac)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(SDL3_PATH "C:/App/SDL3")
    set(SDL3_IMAGE_PATH "C:/App/SDL3_image")

    include_directories(
            ${SDL3_PATH}/include
            ${SDL3_IMAGE_PATH}/include
            ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/src/ecs
            ${PROJECT_SOURCE_DIR}/src/ecs/system
            ${PROJECT_SOURCE_DIR}/src/utils
            ${PROJECT_SOURCE_DIR}/src/vendor
    )
endif()

add_executable(maziac WIN32
        asset/app.rc
        src/main.cpp
        src/Game.cpp
        src/manager/TextureManager.cpp
        src/Map.cpp
        src/GameObject.cpp
        src/utils/Vector2D.cpp
        src/utils/Collision.cpp
        src/ecs/system/CollisionSystem.cpp
        src/vendor/tinyxml2.cpp
        src/manager/AssetManager.cpp
        src/scene/Scene.cpp
        src/ecs/system/EventResponseSystem.cpp
        src/ecs/system/MainMenuSystem.cpp
        src/ecs/system/MouseInputSystem.cpp
        src/ecs/system/MovementSystem.cpp
        src/ecs/system/EnergyDepletionSystem.cpp
        src/ecs/system/TileInteractionSystem.cpp
)

target_link_libraries(maziac
        "C:/App/SDL3/lib/libSDL3.dll.a"
        "C:/App/SDL3_image/lib/libSDL3_image.dll.a"
)

if (MINGW)
    target_link_options(maziac PRIVATE
            -static
            -static-libgcc
            -static-libstdc++
    )
endif()