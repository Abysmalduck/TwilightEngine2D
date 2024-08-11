#include "Window.h"

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

    SDL_GL_SetSwapInterval(1);

    this_window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(this_window);
    this_context = &context;

    SDL_GL_MakeCurrent(this_window, this_context);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        printf("ERROR");
    }

    glEnable(GL_DEPTH_TEST);
}

void Window::update()
{
    glViewport(0, 0, 800, 600);
    glClearColor(0.5f, 0.25f, 0.25f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::size_t i = 0; i < _render_engines.size(); i++)
    {
        _render_engines[i]->draw();
    }

    SDL_GL_SwapWindow(this_window);
}

void Window::addRenderer(RenderEngine* _render_engine)
{
    _render_engine->attachWindow(this);

    _render_engine->init();
    _render_engines.push_back(_render_engine);
}