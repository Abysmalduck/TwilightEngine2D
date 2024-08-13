#pragma once

#include "Movable.h"
#include <string>
#include "Scene.h"

class Object : public Movable
{
private:
    Scene* _attached_scene;
    std::string name;
public:
    Object(const std::string& _name, Scene* attached_scene)
    {
        name = _name;
        _attached_scene = attached_scene;
    }

    const std::string& getName() const
    {
        return name;
    }

    virtual void start()
    {
        //Start Code
    }

    virtual void update()
    {
        //Update code
    }

    
};