#pragma once

#include "Object.h"

class Sprite : public Object
{
public:
    Sprite(std::string name) : Object(name) {}

    std::string texture_path;
    //texture
};

