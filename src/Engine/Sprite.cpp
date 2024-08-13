#include "Sprite.h"

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <SOIL/SOIL.h>


Sprite::Sprite(const std::string& text_path, const std::string& name, Scene* scene) : Object(name, scene) 
{
    SpriteRenderer* eng = nullptr;
    if (scene->getAttachedWindow()->getWindowType() == WINDOW_TYPE_OPENGL)
    {
        eng = (SpriteRenderer*)(((OpenGLWindow*)scene->getAttachedWindow())->getSpriteRenderer());
    }
    else
    {
        logsi("Trying to create sprite in non-opengl window.", ERR);
    }
    

    texture_path = text_path;

    texture_raw = SOIL_load_image(texture_path.c_str(), &width, &height, &channel, SOIL_LOAD_RGB);
    
    glGenTextures(1, &texture_gl);
    glBindTexture(GL_TEXTURE_2D, texture_gl);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_raw);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(texture_raw);
    glBindTexture(GL_TEXTURE_2D, 0);

    eng->addSprite(this);
    logs("Added sprite to render engine");
    
}