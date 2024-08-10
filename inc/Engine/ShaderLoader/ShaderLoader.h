#pragma once

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "DefaultShaders.h"

#include <map>
#include <string>
#include <sstream>

#include "log.h"

class ShaderLoader
{
private:

    ShaderLoader() {}
    ShaderLoader(ShaderLoader&) {}
    void operator=(ShaderLoader&) {}

    std::map<std::string, GLuint> shaders_map = std::map<std::string, GLuint>();

    void loadShader(std::string name, std::string vertex_source, std::string frag_source)
    {
        logs("Compiling shader: " + name);
        

        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        const char* v_char_source = vertex_source.c_str();
        GLint v_size = vertex_source.size();
        glShaderSource(vertex_shader, 1, &v_char_source, &v_size);
        glCompileShader(vertex_shader);

        GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* f_char_source = frag_source.c_str();
        GLint f_size = frag_source.size();
        glShaderSource(frag_shader, 1, &f_char_source, &f_size);
        glCompileShader(frag_shader);

        GLuint sh_program = glCreateProgram();
        glAttachShader(sh_program, vertex_shader);
        glAttachShader(sh_program, frag_shader);
        glLinkProgram(sh_program);

        GLint success;
        GLchar infoLog[512];

        glGetProgramiv(sh_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(sh_program, 512, NULL, infoLog);
            //std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            std::stringstream err_message;
            err_message << "Shader " + name + " compiled with errors!\n";
            err_message << infoLog;

            logsi(err_message.str(), ERR);
        }
        else
        {
            logs("Shader " + name + " compiled successfully");
        }

        shaders_map[name] = sh_program;

        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);
    }
public:
    static ShaderLoader& getInstance()
    {
        static ShaderLoader instance;
        return instance;
    }

    void loadDefaultShaders()
    {
        loadShader("DefaultSpriteShader", sprite_shader_vert, sprite_shader_frag);
    }

    GLuint getShaderByName(std::string name) const 
    {
        return shaders_map.at(name);
    }
        
};