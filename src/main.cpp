#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <Window.h>
#include "SpriteRenderer.h"
#include "ShaderLoader.h"

int main (int ArgCount, char **Args)
{
    bool isRunning = true;
    
    Window win(800, 600);
    win.create();

    ShaderLoader::getInstance().loadDefaultShaders();

    SpriteRenderer spriteRenderer = SpriteRenderer();
    Sprite sprite = Sprite();

    spriteRenderer.addSprite(&sprite);

    win.addRenderer(&spriteRenderer);

    while (isRunning)
    {
        //Events
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }   
        win.update();
    }   
    return 0;
}