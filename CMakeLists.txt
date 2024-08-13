cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME twilight2d)

set (CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} VERSION 0.1)

include_directories(
    inc/
    inc/Engine/
    inc/Engine/RenderEngine/
    inc/Engine/ShaderLoader/
    inc/Engine/Shaderscls
)

if (UNIX)
    include_directories(/usr/local/include/LuaCpp/)
    include_directories(/usr/local/include/SOIL/)
endif (UNIX)

set(SOURCES
    src/main.cpp
    src/Engine/OpenGLWindow.cpp
    src/Engine/RenderEngine/TileMapRenderer.cpp
    src/Engine/RenderEngine/SpriteRenderer.cpp
    src/Engine/Camera.cpp
    src/Engine/Scene.cpp
    src/Engine/Sprite.cpp
    src/Engine/Object.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

if (WIN32)
    set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/GLEW/include")
    set(GLM_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/glm/include")
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/SDL2/include")
    set(LUA_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/lua/include")
    set(LUACPP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/luacpp/include")
    set(SOIL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/SOIL/include")

    message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

    include_directories(${GLEW_INCLUDE_DIRS}
                         ${GLM_INCLUDE_DIRS} 
                         ${SDL2_INCLUDE_DIRS} 
                         ${LUA_INCLUDE_DIRS}
                         ${LUACPP_INCLUDE_DIRS}
                         ${SOIL_INCLUDE_DIRS})

    set(GLEW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/GLEW/glew32.dll")
    set(LUA_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/lua/lua54.dll")
    set(LUACPP_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/luacpp/libluacpp.dll")
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/SDL2/SDL2.dll")
    set(SOIL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/dependecies/SOIL/libsoil.dll")

    
endif ()

find_package(OpenGL REQUIRED OpenGL)
if (UNIX)
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glm REQUIRED)

    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} OpenGL::GL lua luacpp soil)
endif (UNIX)

if (WIN32)
target_link_libraries(${PROJECT_NAME} 
                        ${SDL2_LIBRARIES} 
                        ${GLEW_LIBRARIES} 
                        OpenGL::GL 
                        ${SOIL_LIBRARIES}
                        ${LUA_LIBRARIES} 
                        ${LUACPP_LIBRARIES})
endif(WIN32)




