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

    void object_start()
    {
        for (size_t i = 0; i < known_ids.size(); i++)
        {
            scene_objects.at(known_ids[i])->start();
        }
    }

    void object_update()
    {
        for (size_t i = 0; i < known_ids.size(); i++)
        {
            scene_objects.at(known_ids[i])->update();
        }
    }

    Object* getSceneObjectByID(const unsigned int ID)
    {
        if(scene_objects.find(ID) != scene_objects.end())
        {
            return scene_objects.at(ID);
        }
        return nullptr;
    }

    //Add object to Scene. Returns Object ID
    int addSceneObject(Object* obj)
    {
        last_id = last_id + 1;
        scene_objects[last_id] = obj;
        known_ids.push_back(last_id);

        logs("added object to scene! Name: " + obj->getName());

        return last_id;
    }

    void removeSceneObjectByID(unsigned long int ID)
    {
        auto known_ids_iter = std::find(known_ids.begin(), known_ids.end(), ID);
        if(known_ids_iter != known_ids.end())
        {
            known_ids.erase(known_ids_iter);
            delete scene_objects.at(ID);
            scene_objects.erase(ID);
        }
        else
        {
            logsi("Unable to find Object with ID: " + std::to_string(ID), ERR);
            return;
        }
    }

    Window* getAttachedWindow()
    {
        return attached_window;
    }

    static void initRootLibrary();

    static std::shared_ptr<LuaCpp::Registry::LuaLibrary>& getSceneLib();
};