#pragma once

class Sprite;

#include "SpriteRenderer.h"

#include "Object.h"
#include "Scene.h"
#include "log.h"

class Sprite : public Object
{
private:
    std::string texture_path = "../game/resources/textures/default.png";
    unsigned char* texture_raw;
    int width = 0;
    int height = 0;
    int channel = 0;

    GLuint texture_gl;
public:
    Sprite(const std::string& text_path, const std::string& name, Scene* scene);

    GLuint getTexture() { return texture_gl;}

    void update() override
    {
        
    }

    void start() override
    {

    }
};

