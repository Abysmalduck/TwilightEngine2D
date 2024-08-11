#include "Sprite.h"

Sprite::Sprite(std::string name, Scene* scene) : Object(name, scene) 
{
    SpriteRenderer* eng = (SpriteRenderer*)(scene->getAttachedWindow()->getSpriteRenderer());

    eng->addSprite(this);
    logs("Added sprite to render engine");
    
}