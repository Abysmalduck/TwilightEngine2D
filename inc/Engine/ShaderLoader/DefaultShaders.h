#pragma once

#include <string>

const std::string sprite_shader_vert =
R"(
    #version 330 core

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
                
    layout (location = 0) in vec3 position;

    void main()
    {
        gl_Position = projection * view * model * vec4(position, 1.0);
    }
)";

const std::string sprite_shader_frag =
R"(
    #version 330 core
                
    out vec4 color;

    void main()
    {
        color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";