#include "PlayerMovementComponent.h"
#include <GameObject.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <Rigidbody.h>

void Roguelike::PlayerMovementComponent::Update(float dt)
{
	auto rb = this->GetGameObject()
					->GetComponent<GameEngine::Rigidbody>();
	if (!rb)
		return;

    sf::Vector2f direction{ 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        direction.y -= 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        direction.y += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        direction.x -= 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        direction.x += 1.f;

    float length =
        std::sqrt(direction.x * direction.x +
            direction.y * direction.y);

    if (length > 0.f)
        direction /= length;

    rb->velocity = direction * speed;
}
