#pragma once

class Scene;

#include <vector>
#include <map>
#include <algorithm>
#include <LuaCpp.hpp>
#include "Window.h"

#include "Object.h"
#include "log.h"

class Scene
{
private:
    Window* attached_window;

    std::map<unsigned long int, Object*> scene_objects = std::map<unsigned long int, Object*>();
    std::vector<unsigned long int> known_ids = std::vector<unsigned long int>();
    unsigned long int last_id = 0;

    static std::shared_ptr<LuaCpp::Registry::LuaLibrary> scene_lua_lib;
public:
    Scene(Window* root_window)
    {
        attached_window = root_window;
    }

    virtual void scene_update() { };
    virtual void scene_start() { };

    void object_start();
    void object_update();

    Object* getSceneObjectByID(const unsigned int ID);

    //Add object to Scene. Returns Object ID
    int addSceneObject(Object* obj);

    void removeSceneObjectByID(unsigned long int ID);

    Window* getAttachedWindow()
    {
        return attached_window;
    }

    static void initRootLibrary();

    static std::shared_ptr<LuaCpp::Registry::LuaLibrary>& getSceneLib();
};