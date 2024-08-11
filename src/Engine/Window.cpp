#include "Window.h"
#include "SpriteRenderer.h"
#include "TileMapRenderer.h"

Window::Window(GLint width, GLint height, std::string title)
{
    if (width < 640)
    {
        width = 640;
    }

    if (height < 480)
    {
        height = 480;
    }

    win_title = title; 
}

void Window::create()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetSwapInterval(0);

    this_window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(this_window);
    this_context = &context;

    SDL_GL_MakeCurrent(this_window, this_context);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        logsi("Unable to initialize GLEW", ERR);
        return;
    }

    glEnable(GL_DEPTH_TEST);

    spriteRenderEngine = new SpriteRenderer();
    spriteRenderEngine->init();
    tileMapRenderEngine = new TileMapRenderer();
    tileMapRenderEngine->init();
}

void Window::update()
{
    glViewport(0, 0, 800, 600);
    glClearColor(0.5f, 0.25f, 0.25f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    spriteRenderEngine->draw();
    tileMapRenderEngine->draw();

    SDL_GL_SwapWindow(this_window);
}

#include <LuaCpp.hpp>
extern Window* current_window;

// LUA CXX WINDOW LIB

void CXX_window_change_resolution(unsigned int w, unsigned int h)
{
    //TODO
}

extern "C"
{
    int C_window_change_resolution(lua_State* L)
    {
        //TODO
        return 0;
    }
}