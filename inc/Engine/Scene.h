#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <LuaCpp.hpp>

#include "Object.h"
#include "log.h"

class Scene
{
private:
    std::map<unsigned long int, Object*> scene_objects = std::map<unsigned long int, Object*>();
    std::vector<unsigned long int> known_ids = std::vector<unsigned long int>();
    unsigned long int last_id = 0;

    static std::shared_ptr<LuaCpp::Registry::LuaLibrary> scene_lua_lib;
public:
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

    static void initRootLibrary();

    static std::shared_ptr<LuaCpp::Registry::LuaLibrary>& getSceneLib();
};