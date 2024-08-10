#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Movable
{
private:
    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 rotation = glm::vec3(0,0,0);
    GLfloat angle = 0.0;

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

    const glm::mat4* getModelMatrix()
    {
        model = glm::mat4(1);

        model = glm::scale(model, scale);
        //model = glm::rotate(model, angle, rotation);
        model = glm::translate(model, position);

        return &model;
    }
};
