#pragma once

#include "Movable.h"
#include <string>

class Object : public Movable
{
private:
    std::string name;
public:
    Object(std::string _name)
    {
        name = _name;
    }

    const std::string& getName() const
    {
        return name;
    }

    virtual void update()
    {
        //Update code
    }

    virtual void start()
    {
        //Start Code
    }
};