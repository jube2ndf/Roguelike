#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Component.h"
namespace GameEngine {
    class SpriteRenderer :
        public Component
    {
    public:
        SpriteRenderer(GameObject* owner, 
            const sf::Texture& texture) 
            :Component(owner),
            _sprite(texture)
        {
            
        }
    protected:
        sf::Sprite _sprite;

        int sortingLayer = 0;
    };
}