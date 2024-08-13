#pragma once

#include <string>

const std::string sprite_shader_vert =
R"(
    #version 330 core

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
                
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec2 tex_uv;

    out vec2 tex_uv_frag;

    void main()
    {
        tex_uv_frag = tex_uv;
        gl_Position = projection * view * model * vec4(position, 1.0);
    }
)";

const std::string sprite_shader_frag =
R"(
    #version 330 core
                
    out vec4 color;
    in vec2 tex_uv_frag;

    uniform sampler2D sprite_texture;

    void main()
    {
        color = texture(sprite_texture, tex_uv_frag);
    }
)";