#pragma once

class Sprite;

#include "SpriteRenderer.h"

#include "Object.h"
#include "Scene.h"
#include "log.h"

class Sprite : public Object
{
private:
    
public:
    Sprite(std::string name, Scene* scene);

    std::string texture_path;

    void update() override
    {
        
    }

    void start() override
    {

    }
};

