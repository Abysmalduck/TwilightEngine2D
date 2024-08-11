#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <Window.h>
#include "SpriteRenderer.h"
#include "ShaderLoader.h"
#include "LuaEngine.h"
#include "Scene.h"

#define DEFAULT_LUA_PATH "../lua/"

Window* current_window;

int main (int ArgCount, char **Args)
{
    std::string lua_path = DEFAULT_LUA_PATH;

    if (ArgCount == 2)
    {
        lua_path = std::string(Args[1]);
    }

    LuaEngine luaEngine;
    if(luaEngine.init(lua_path) != 0)
    {
        logsi("Lua engine initialization error. Exiting.", ERR);
        return -1;
    }

    current_window = new Window(800, 600);
    current_window->create();
    Scene* scene = new Scene();
    current_window->attachScene(scene);

    ShaderLoader::getInstance().loadDefaultShaders();
    SpriteRenderer spriteRenderer = SpriteRenderer();
    current_window->addRenderer(&spriteRenderer);

    Scene::initRootLibrary();
    luaEngine.addLibrary(Scene::getSceneLib());

    bool isRunning = true;

    luaEngine.callRootStart();
    while (isRunning)
    {
        //Events
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }   

        luaEngine.callRootUpdate();

        //Window Update
        current_window->update();
    }   
    return 0;
}