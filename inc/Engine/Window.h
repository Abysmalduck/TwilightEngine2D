#pragma once

class Window;

#include <string>
#include "Scene.h"

enum WINDOW_TYPE
{
    WINDOW_TYPE_NONE,
    WINDOW_TYPE_OPENGL
    //maybe other types
};

class Window
{
protected:
    std::string win_title = "Twilight2D window";

    int win_width = 800;
    int win_height = 600;

    Scene* window_scene;

    WINDOW_TYPE win_type = WINDOW_TYPE_NONE;
public:
    virtual void create() = 0;
    virtual void start() = 0;
    virtual void update() = 0;

    virtual int getWindowHeight() = 0;
    virtual int getWindowWidth() = 0;

    virtual void attachScene(Scene* scene) { window_scene = scene; }

    Scene* getScene() { return window_scene; }; 

    WINDOW_TYPE getWindowType() {return win_type;}
};