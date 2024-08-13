#pragma once

class OpenGLWindow;

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <vector>

#include "RenderEngine.h"
#include "stdio.h"

#include "Window.h"

class OpenGLWindow : public Window
{
private:
    SDL_Window* this_window;
    SDL_GLContext* this_context;

    //Render Engines
    RenderEngine* spriteRenderEngine;
    RenderEngine* tileMapRenderEngine;

public:
    OpenGLWindow(GLint width = 800, GLint height = 600, std::string title = "Twilight2D window");

    void create() override;

    void start() override;
    void update() override;

    int getWindowWidth() override { return win_width; }

    int getWindowHeight() override { return win_height; }

    RenderEngine* getSpriteRenderer()
    {
        return spriteRenderEngine;
    }

    RenderEngine* getTileMapRenderer()
    {
        return tileMapRenderEngine;
    }
};