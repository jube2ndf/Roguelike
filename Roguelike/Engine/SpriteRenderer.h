#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Component.h"
#include "EngineAPI.h"
namespace GameEngine {
    class ENGINE_API SpriteRenderer :
        public Component
    {
    public:
        SpriteRenderer(GameObject* owner, 
            const sf::Texture& texture) 
            :Component(owner),
            _sprite(texture)
        {
            const float TILE_SIZE = 64.f;

            _sprite.setScale(
                { TILE_SIZE / texture.getSize().x,
                TILE_SIZE / texture.getSize().y }
            );
        }
        sf::Sprite& GetSprite() {
            return this->_sprite;
        }
    protected:
        sf::Sprite _sprite;

        int sortingLayer = 0;
    };
}