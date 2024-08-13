#include "SpriteRenderer.h"

#include "ShaderLoader.h"
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

void SpriteRenderer::init()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &TEXBUFF);
    glBindBuffer(GL_ARRAY_BUFFER, TEXBUFF);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindVertexArray(0);
}

void SpriteRenderer::draw()
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
        glBindTexture(GL_TEXTURE_2D, sprites[i]->getTexture());
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        GLuint err = glGetError();
        if (err != 0)
        {
            //printf("ERROR : %lu\n", err);
            logsi("OpenGL error:" + std::to_string(err), ERR);
        }
    }

    glBindVertexArray(0);
}