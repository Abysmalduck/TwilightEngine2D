#include "Scene.h"
#include "Sprite.h"
#include "Window.h"
#include <LuaCpp.hpp>

extern Window* current_window;

std::shared_ptr<LuaCpp::Registry::LuaLibrary> Scene::scene_lua_lib = std::make_shared<LuaCpp::Registry::LuaLibrary>("tweng_scene");

// LUA CXX SCENE LIBRARY

int CXX_add_object_root_scene(const char* object_name, const char* object_type)
{
    Object* obj;

    if (std::string(object_type)  == "sprite")
    {
        obj = new Sprite(std::string(object_name));
        unsigned long int obj_id = current_window->getScene()->addSceneObject(obj);
        return obj_id;
    }
    else
    {
        logsi("Unknown object type: " + std::string(object_type), ERR);
        return -1;
    }
    return -1;
}

// LUA C SCENE LIBRARY

extern "C"
{
    //  LUA ADD OBJECT TO ROOT SCENE
    //  
    //  Arguments:
    //      1) Name of object
    //      2) Type of object (Sprite Tilemap)
    int C_add_object_root_scene(lua_State* L)
    {
        int args_num = lua_gettop(L);

        if (args_num != 2)
        {
            return 0;
        }

        const char* obj_name = lua_tostring(L, 1);
        const char* obj_type = lua_tostring(L, 2);

        unsigned long int obj_id = CXX_add_object_root_scene(obj_name, obj_type);
        lua_pushnumber(L, static_cast<lua_Number>(obj_id));

        return 1;
    }
}

void Scene::initRootLibrary()
{
    scene_lua_lib->AddCFunction("add_object", C_add_object_root_scene);
}

std::shared_ptr<LuaCpp::Registry::LuaLibrary>& Scene::getSceneLib()
{
    return scene_lua_lib;
}