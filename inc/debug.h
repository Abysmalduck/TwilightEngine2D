#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>

void printMatrix(const glm::mat4* mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", (*mat)[i][j]);
        }
        printf("\n");
    }
}