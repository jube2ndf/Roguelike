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
            auto size = _sprite.getTexture().getSize();

            _sprite.setOrigin(
                { size.x * 0.5f,
                size.y * 0.5f }
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