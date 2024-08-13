#pragma once

class RenderEngine;

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "OpenGLWindow.h"

class RenderEngine
{
private:
    const OpenGLWindow* attached_window;
public:
    virtual void init() = 0;

    virtual void draw() = 0;

    virtual ~RenderEngine() {}

    void attachWindow(const OpenGLWindow* window)
    {
        attached_window = window;
    }
};