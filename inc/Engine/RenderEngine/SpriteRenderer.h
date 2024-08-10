#pragma once

#include "RenderEngine.h"
#include "Sprite.h"
#include "ShaderLoader.h"
#include "Camera.h"

#include <vector>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "debug.h"

class SpriteRenderer : public RenderEngine
{
private:
    Camera camera = Camera();

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    GLuint shader_program = 0;

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
    }

    Camera* getCameraPtr()
    {
        return &camera;
    }

    void init() override
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VERTS), VERTS, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void draw() override
    {
        GLuint shader = ShaderLoader::getInstance().getShaderByName("DefaultSpriteShader");

        glUseProgram(shader);

        GLint model_mat_uniform = glGetUniformLocation(shader, "model");
        GLint view_mat_uniform = glGetUniformLocation(shader, "view");
        GLint proj_mat_uniform = glGetUniformLocation(shader, "projection");

        const glm::mat4* projection_mat = this->camera.getProjMatrixPtr();
        const glm::mat4* view_mat = this->camera.getModelMatrix();


        glUniformMatrix4fv(view_mat_uniform, 1, GL_FALSE, glm::value_ptr(*view_mat));
        glUniformMatrix4fv(proj_mat_uniform, 1, GL_FALSE, glm::value_ptr(*projection_mat));

        glBindVertexArray(VAO);

        for (std::size_t i = 0; i < sprites.size(); i++)
        {
            const glm::mat4* mode_mat = sprites[i]->getModelMatrix();
            glUniformMatrix4fv(model_mat_uniform, 1, GL_FALSE, glm::value_ptr(*mode_mat));
            glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

            GLuint err = glGetError();
            if (err != 0)
            {
                printf("ERROR : %lu\n", err);
            }
        }

        glBindVertexArray(0);
    }
    void addSprite(Sprite* sprite)
    {
        sprites.push_back(sprite);
    }

    ~SpriteRenderer()
    {

    }
};