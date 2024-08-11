#pragma once

#include "Camera.h"

#include "RenderEngine.h"
#include "Sprite.h"

#include <vector>

class SpriteRenderer : public RenderEngine
{
private:
    Camera camera = Camera();

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    GLuint shader_program;

    std::vector<Sprite*> sprites = std::vector<Sprite*>();

    const GLfloat VERTS[12] = 
        {
            0.5f,  0.5f, 0.0f,  // Top Right
            0.5f, -0.5f, 0.0f,  // Bottom Right
            -0.5f, -0.5f, 0.0f,  // Bottom Left
            -0.5f,  0.5f, 0.0f   // Top Left 
        };


    const GLuint indices[6] = 
        {  
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
        };

public:

    SpriteRenderer()
    {
        camera.setPosition(0,0,-1);
        camera.setRatio(1.33);
    }

    Camera* getCameraPtr()
    {
        return &camera;
    }

    void init() override;

    void draw() override;

    void addSprite(Sprite* sprite)
    {
        sprites.push_back(sprite);
    }

    ~SpriteRenderer()
    {

    }
};