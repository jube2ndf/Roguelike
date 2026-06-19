#include "SimpleAttack.h"
#include <GameObject.h>
#include <SFML/Window/Mouse.hpp>
#include <InputGame.h>
#include "AttackComponent.h"
#include <EventBus.h>
#include "CreateWeapon.h"
#include "Math.h"

Roguelike::SimpleAttack::SimpleAttack(GameEngine::GameObject* owner)
    : Component(owner)
{

}

void Roguelike::SimpleAttack::Update(float dt)
{
    if (!this->used)
        return;
    auto mousePos = GameEngine::InputGame::mouseWorldPosition;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (this->used->CanAttack())
        {
            auto transform =
                this->GetGameObject()->GetComponent<GameEngine::TransformComponent>();
            sf::Vector2f playerPos =
                transform->GetWorldPosition();
            auto direction = Math::Normalize(mousePos - playerPos);
            auto attack =
                this->GetGameObject()->GetComponent<AttackComponent>();
            if (attack)
            {
                CreateWeapon dto;
                dto.data.direction = direction;
                dto.data.position = playerPos;
                dto.type = attack->type;
                dto.source = this->GetGameObject();
                GameEngine::EventBus::Emit(dto);
                this->used->ResetCooldown();
            }
        }
    }
}
