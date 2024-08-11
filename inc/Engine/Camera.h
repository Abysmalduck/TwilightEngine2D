#pragma once

class Camera;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Movable.h"

class Camera : public Movable
{
private:
    glm::mat4 proj_matrix;
public:
    Camera(GLfloat ratio = 1.0);

    void setRatio(GLfloat ratio = 1.0)
    {
        proj_matrix = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.1f, 100.0f );
    }

    const glm::mat4* getProjMatrixPtr() const 
    {
        return &proj_matrix;
    }
};