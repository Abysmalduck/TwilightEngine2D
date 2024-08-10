#pragma once

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Window.h"

class RenderEngine
{
private:
    const Window* attached_window;
public:
    virtual void init() = 0;

    virtual void draw() = 0;

    virtual ~RenderEngine() {}

    void attachWindow(const Window* window)
    {
        attached_window = window;
    }
};