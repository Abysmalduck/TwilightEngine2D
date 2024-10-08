#pragma once

class SpriteRenderer;

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

    GLuint TEXBUFF;

    GLuint shader_program;

    std::vector<Sprite*> sprites = std::vector<Sprite*>();

    const GLfloat verts[12] = 
    {
        1.0f,  1.0f, 0.0f,  // Top Right
        1.0f, -1.0f, 0.0f,  // Bottom Right
        -1.0f, -1.0f, 0.0f,  // Bottom Left
        -1.0f,  1.0f, 0.0f   // Top Left 
    };


    const GLuint indices[6] = 
    {  
        0, 1, 2,
        2, 3, 0
        //0, 1, 3,  // First Triangle
        //1, 2, 3   // Second Triangle
    };

    const GLfloat tex_coords[12] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
        /*1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f*/
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