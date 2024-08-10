#pragma once

#include "Movable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

class Camera : public Movable
{
private:
    glm::mat4 proj_matrix;
public:
    Camera(GLfloat ratio = 1.0)
    {
        GLfloat w_ratio = (ratio);
        GLfloat h_ratio = (1 / ratio);

        proj_matrix = glm::ortho(-w_ratio, w_ratio, -h_ratio, h_ratio, 0.1f, 100.0f );
    }

    const glm::mat4* getProjMatrixPtr() const 
    {
        return &proj_matrix;
    }
};