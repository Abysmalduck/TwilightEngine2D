#pragma once

class Window;

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <vector>

#include "RenderEngine.h"
#include "stdio.h"

#include "Scene.h"

class Window
{
private:
    SDL_Window* this_window;
    SDL_GLContext* this_context;

    GLint win_width = 800;
    GLint win_height = 600;

    std::string win_title = "Twilight2D window";

    //Render Engines
    RenderEngine* spriteRenderEngine;
    RenderEngine* tileMapRenderEngine;

    Scene* window_scene;

public:
    Window(GLint width = 800, GLint height = 600, std::string title = "Twilight2D window");

    void create();

    void update();

    GLint getWindowWidth()
    {
        return win_width;
    }

    GLint getWindowHeight()
    {
        return win_height;
    }

    void attachScene(Scene* scene)
    {
        window_scene = scene;
    }

    Scene* getScene()
    {
        return window_scene;
    }

    RenderEngine* getSpriteRenderer()
    {
        return spriteRenderEngine;
    }

    RenderEngine* getTileMapRenderer()
    {
        return tileMapRenderEngine;
    }
};