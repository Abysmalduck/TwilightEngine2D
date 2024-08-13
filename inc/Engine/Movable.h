#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

class Movable
{
private:
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 rotation = glm::vec3(0,0,0);

    glm::vec3 scale = glm::vec3(1,1,1);

    glm::mat4 model = glm::mat4(1);
public:
    const glm::vec3* getPosition() const
    {
        return &position;
    }

    void setPosition(double x, double y, double z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    const glm::vec3* getScale() const
    {
        return &scale;
    }

    void setScale(double x, double y, double z)
    {
        scale = glm::vec3(x, y, z);
    }

    void setRotationEuler(double x, double y, double z)
    {
        rotation = glm::vec3(x, y, z);
    }

    const glm::vec3* getRotationEuler() const
    {
        return &rotation;
    }

    const glm::mat4* getModelMatrix()
    {
        model = glm::mat4(1);

        model = glm::translate(model, position);
        
        model = model * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);

        model = glm::scale(model, scale);
        
        return &model;
    }
};
