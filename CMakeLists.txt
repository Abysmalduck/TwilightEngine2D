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
    src/Engine/Sprite.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

if (WIN32)
    set(GLEW_INCLUDE_DIRS "C:/Program Files/GLEW/include/")
    set(GLM_INCLUDE_DIRS "C:/Program Files/glm")
    set(SDL2_INCLUDE_DIRS "C:/Program Files/SDL2/x86_64-w64-mingw32/include")
    set(LUA_INCLUDE_DIRS "C:/lua-5.4.7")
    set(LUACPP_INCLUDE_DIRS "C:/luacpp-bin/include")

    include_directories(${GLEW_INCLUDE_DIRS}
                         ${GLM_INCLUDE_DIRS} 
                         ${SDL2_INCLUDE_DIRS} 
                         ${LUA_INCLUDE_DIRS}
                         ${LUACPP_INCLUDE_DIRS})

    set(GLEW_LIBRARIES "C:/Program Files/GLEW/lib/Release/x64/glew32.lib")

    set(LUA_LIBRARIES "C:/lua-5.4.7/bin/lua54.dll")
    set(LUACPP_LIBRARIES "C:/luacpp-bin/libluacpp.dll")
    set(SDL2_LIBRARIES "C:/Program Files/SDL2/x86_64-w64-mingw32/bin/SDL2.dll")

    
endif ()



find_package(OpenGL REQUIRED OpenGL)
if (UNIX)
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glm REQUIRED)

    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} OpenGL::GL lua luacpp)
endif (UNIX)

if (WIN32)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} OpenGL::GL ${LUA_LIBRARIES} ${LUACPP_LIBRARIES})
endif(WIN32)




