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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetSwapInterval(0);

    this_window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(this_window);
    this_context = &context;

    glewExperimental = GL_TRUE;

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        const char* err_mesg = (char*)glewGetErrorString(status);

        logsi("Unable to initialize GLEW", ERR);
        logsi(std::string(err_mesg), ERR);
        return;
    }

    glEnable(GL_DEPTH_TEST);

    spriteRenderEngine = new SpriteRenderer();
    spriteRenderEngine->init();
    tileMapRenderEngine = new TileMapRenderer();
    tileMapRenderEngine->init();

    logs("OpenGL initializied. OpenGL String:" + std::string((const char*)glGetString(GL_VERSION)));
}

void Window::update()
{
    glViewport(0, 0, 800, 600);
    glClearColor(0.25f, 0.0f, 0.0f, 0.f);
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