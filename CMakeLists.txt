cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME twilight2d)

set (CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} VERSION 0.1)

include_directories(
    inc/
    inc/Engine/
    inc/Engine/RenderEngine/
    inc/Engine/ShaderLoader/
    inc/Engine/Shaders
)

if (UNIX)
    include_directories(/usr/local/include/LuaCpp/)
endif (UNIX)

set(SOURCES
    src/main.cpp
    src/Engine/Window.cpp
    src/Engine/RenderEngine/TileMapRenderer.cpp
    src/Engine/RenderEngine/SpriteRenderer.cpp
    src/Engine/Camera.cpp
    src/Engine/Scene.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenGL REQUIRED OpenGL)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} OpenGL::GL glm::glm lua luacpp)
