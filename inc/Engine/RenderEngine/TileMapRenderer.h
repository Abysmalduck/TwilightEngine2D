#pragma once

#include "RenderEngine.h"

class TileMapRenderer : public RenderEngine
{
public:
    void init() override
    {
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);


    }

    void draw() override
    {
        // TODO Instancing https://learnopengl.com/Advanced-OpenGL/Instancing
    }

    ~TileMapRenderer()
    {

    }
};