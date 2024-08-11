#include "Camera.h"

Camera::Camera(GLfloat ratio)
{
    GLfloat w_ratio = (ratio);
    GLfloat h_ratio = (1 / ratio);

    proj_matrix = glm::ortho(-w_ratio, w_ratio, -1.0f, 1.0f, 0.1f, 100.0f );
}