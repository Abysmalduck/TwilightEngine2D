#pragma once

class Object;

#include "Movable.h"
#include <string>
#include "Scene.h"
#include <LuaCpp.hpp>

class Object : public Movable
{
private:
    Scene* _attached_scene;
    std::string name;

    bool update_file_exists = false;
    bool start_file_exists = false;

    unsigned int ID = 0;

    std::shared_ptr<LuaCpp::Engine::LuaTNumber> lua_ID;

public:
    Object(const std::string& _name, Scene* attached_scene);

    const std::string& getName() const
    {
        return name;
    }

    virtual void start();

    virtual void update();

    void attachID(unsigned int _ID)
    {
        ID = _ID;
        lua_ID = std::make_shared<LuaCpp::Engine::LuaTNumber>(ID);
    }

    void luaBindID();
};