#include "Object.h"

#include <filesystem>
#include "LuaEngine.h"

extern LuaEngine* luaEngine;

Object::Object(const std::string& _name, Scene* attached_scene)
{
    name = _name;
    _attached_scene = attached_scene;

    //check if lua script for object exists

    std::filesystem::path update_file = std::filesystem::path(luaEngine->getLuaPath()) / std::filesystem::path(_name + "/update.lua");
    std::filesystem::path start_file = std::filesystem::path(luaEngine->getLuaPath()) / std::filesystem::path(_name + "/start.lua");

    update_file_exists = std::filesystem::exists(update_file);
    start_file_exists = std::filesystem::exists(start_file);

    if (update_file_exists)
    {
        luaEngine->addScriptToContext(name + "_start", start_file.string());
    }
    if (start_file_exists)
    {
        luaEngine->addScriptToContext(name + "_update", update_file.string());
    }
}

void Object::start()
{
    if(!start_file_exists) return;
    luaBindID();
    luaEngine->luaCallScript(name + "_start");
}

void Object::update()
{
    if(!update_file_exists) return;
    luaBindID();
    luaEngine->luaCallScript(name + "_update");
}

void Object::luaBindID()
{
    luaEngine->getContextPtr()->AddGlobalVariable("this_id", lua_ID);
}