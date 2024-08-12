#include "Scene.h"
#include "Sprite.h"
#include "Window.h"
#include <LuaCpp.hpp>

extern Window* current_window;

std::shared_ptr<LuaCpp::Registry::LuaLibrary> Scene::scene_lua_lib = std::make_shared<LuaCpp::Registry::LuaLibrary>("tweng_scene");

// LUA CXX SCENE LIBRARY

int CXX_scene_add_object(const char* object_name, const char* object_type)
{
    Object* obj;

    if (std::string(object_type)  == "sprite")
    {
        obj = new Sprite(std::string(object_name), current_window->getScene());
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

int CXX_object_translate(const unsigned int obj_ID, double x, double y, double z)
{
    Object* obj_to_move = current_window->getScene()->getSceneObjectByID(obj_ID);
    return 0;
}

int CXX_object_set_position(const unsigned int obj_ID, double x, double y, double z)
{
    Object* obj_to_move = current_window->getScene()->getSceneObjectByID(obj_ID);
    if (obj_to_move == nullptr)
    {
        return -1;
    }
    obj_to_move->setPosition(x, y, z);
    return 0;
}

int CXX_object_set_scale(const unsigned int obj_ID, double x, double y)
{
   Object* obj_to_scale = current_window->getScene()->getSceneObjectByID(obj_ID); 
   if (obj_to_scale == nullptr)
    {
        return -1;
    }
    obj_to_scale->setScale(x, y, 1);
    return 0;   
}

int CXX_object_set_rotation_euler(const unsigned int obj_ID, double x, double y, double z)
{
    Object* obj_to_scale = current_window->getScene()->getSceneObjectByID(obj_ID); 
    if (obj_to_scale == nullptr)
    {
        return -1;
    }
    obj_to_scale->setRotationEuler(x, y, z);
    return 0; 
}

// LUA C SCENE LIBRARY

extern "C"
{
    //  LUA ADD OBJECT TO ROOT SCENE
    //  
    //  Arguments:
    //      1) Name of object
    //      2) Type of object (Sprite Tilemap)
    int C_scene_add_object(lua_State* L)
    {
        int args_num = lua_gettop(L);

        if (args_num != 2)
        {
            return 0;
        }

        const char* obj_name = lua_tostring(L, 1);
        const char* obj_type = lua_tostring(L, 2);

        unsigned long int obj_id = CXX_scene_add_object(obj_name, obj_type);
        lua_pushnumber(L, static_cast<lua_Number>(obj_id));

        return 1;
    }

    int C_object_translate(lua_State* L)
    {
        int args_num = lua_gettop(L); 

        return 0;
    }

    int C_object_set_position(lua_State* L)
    {
        int args_num = lua_gettop(L);
        if (args_num != 4)
        {
            return 0;
        }

        unsigned int ID = lua_tonumber(L,1);
        double _obj_x = lua_tonumber(L, 2);
        double _obj_y = lua_tonumber(L, 3);
        double _obj_z = lua_tonumber(L, 4);

        int result_code = CXX_object_set_position(ID, _obj_x, _obj_y, _obj_z);

        if (result_code != 0)
        {
            logsi("Item with ID: " + std::to_string(ID) + " not found", WARN);
        }

        return 0;
    }

    int C_object_set_scale(lua_State* L)
    {
        int args_num = lua_gettop(L);
        if (args_num != 3)
        {
            return 0;
        }

        unsigned int ID = lua_tonumber(L, 1);
        double _scale_x = lua_tonumber(L, 2);
        double _scale_y = lua_tonumber(L, 3);

        int result_code = CXX_object_set_scale(ID, _scale_x, _scale_y);

        if (result_code != 0)
        {
            logsi("Item with ID: " + std::to_string(ID) + " not found", WARN);
        }

        return 0;
    }

    int C_object_set_rotation_euler(lua_State* L)
    {
        int args_num = lua_gettop(L);
        if (args_num != 4)
        {
            return 0;
        }
        unsigned int ID = lua_tonumber(L, 1);
        double _rot_x = lua_tonumber(L, 2);
        double _rot_y = lua_tonumber(L, 3);
        double _rot_z = lua_tonumber(L, 4);

        int result_code = CXX_object_set_rotation_euler(ID, _rot_x, _rot_y,_rot_z);

        if (result_code != 0)
        {
            logsi("Item with ID: " + std::to_string(ID) + " not found", WARN);
        }

        return 0;
    }
}

void Scene::initRootLibrary()
{
    scene_lua_lib->AddCFunction("add_object", C_scene_add_object);
    scene_lua_lib->AddCFunction("object_set_position", C_object_set_position);
    scene_lua_lib->AddCFunction("object_set_scale", C_object_set_scale);
    scene_lua_lib->AddCFunction("object_set_rotation_euler", C_object_set_rotation_euler);
}

std::shared_ptr<LuaCpp::Registry::LuaLibrary>& Scene::getSceneLib()
{
    return scene_lua_lib;
}