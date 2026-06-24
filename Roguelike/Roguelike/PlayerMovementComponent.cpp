#include "PlayerMovementComponent.h"
#include <GameObject.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <TransformComponent.h>
#include <Rigidbody.h>
#include "StatsComponent.h"
#include "EventPlayerDie.h"
#include <EventBus.h>

void Roguelike::PlayerMovementComponent::Update(float dt)
{
    if (!_owner->IsAlive())
    {
        EventPlayerDied dto;
        dto.boss = _owner;
        GameEngine::EventBus::Emit(dto);
        return;
    }
    auto* go = GetGameObject();
    auto* transform = go->GetComponent<GameEngine::TransformComponent>();

    if (!transform) return;

    sf::Vector2f move{ 0.f, 0.f };
    float speed = this->_owner->GetComponent<StatsComponent>()->GetStat(StatType::MoveSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        move.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        move.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        move.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        move.y += speed;

    auto* rb = go->GetComponent<GameEngine::Rigidbody>();
    rb->velocity = move;
}
