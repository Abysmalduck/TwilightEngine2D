#include <chrono>

#define SDL_MAIN_HANDLED

#include "OpenGLWindow.h"
#include "SpriteRenderer.h"
#include "ShaderLoader.h"
#include "LuaEngine.h"
#include "Scene.h"

#define DEFAULT_LUA_PATH "../game/lua/"

Window* current_window;
LuaEngine* luaEngine;

double engine_time = 0.0;
double engine_frame_time = 16.6;
std::shared_ptr<LuaCpp::Registry::LuaLibrary> tweng_lua_lib = std::make_shared<LuaCpp::Registry::LuaLibrary>("tweng");

void initLuaLibraries(LuaEngine* eng);

int main (int ArgCount, char **Args)
{
    LogManager::getInstance().init();

    std::string lua_path = DEFAULT_LUA_PATH;

    if (ArgCount == 2)
    {
        lua_path = std::string(Args[1]);
    }

    luaEngine = new LuaEngine();
    if(luaEngine->init(lua_path) != 0)
    {
        logsi("Lua engine initialization error. Exiting.", ERR);
        return -1;
    }

    current_window = new OpenGLWindow(800, 600);
    current_window->create();
    Scene* scene = new Scene(current_window);
    current_window->attachScene(scene);

    ShaderLoader::getInstance().loadDefaultShaders();

    initLuaLibraries(luaEngine);

    bool isRunning = true;

    luaEngine->callRootStart();

    current_window->start();
    while (isRunning)
    {
        auto frame_start_point = std::chrono::steady_clock::now();
        //Events
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }   

        luaEngine->callRootUpdate();

        //Window Update
        current_window->update();

        auto frame_stop_point = std::chrono::steady_clock::now();

        int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(frame_stop_point - frame_start_point).count();
        engine_frame_time = ((double)(duration)) / 1000000.0f;
        engine_time += engine_frame_time;
    }   
    return 0;
}

//LUA C LIBRARY
extern "C"
{
    int C_tweng_get_frametime(lua_State* L)
    {
        lua_pushnumber(L, engine_frame_time);
        return 1;
    }

    int C_tweng_get_time(lua_State* L)
    {
        lua_pushnumber(L, engine_time);
        return 1;
    }
}

void initLuaLibraries(LuaEngine* eng)
{
    //TWENG LIBRARY
    tweng_lua_lib->AddCFunction("get_frametime", C_tweng_get_frametime);
    tweng_lua_lib->AddCFunction("get_time", C_tweng_get_time);
    eng->addLibrary(tweng_lua_lib);

    Scene::initRootLibrary();
    eng->addLibrary(Scene::getSceneLib());

}