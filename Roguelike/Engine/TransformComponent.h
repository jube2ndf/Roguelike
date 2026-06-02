#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>
namespace GameEngine {
    class ENGINE_API TransformComponent :
        public Component
    {
	public:
		static constexpr bool Unique = true;
		static constexpr bool Required = true;

		TransformComponent(GameObject* gameObject):Component(gameObject){}

		void Update(float deltaTime) override;

		void MoveBy(const sf::Vector2f& offset);
		void RotateBy(float offset);
		void ScaleBy(const sf::Vector2f& scaleOffset);

		sf::Vector2f GetWorldPosition() const;
		float GetWorldRotation() const;
		sf::Vector2f GetWorldScale() const;

	private:
		sf::Vector2f _position = { 0, 0 };
		float _rotation = 0.f;
		sf::Vector2f _scale = { 1, 1 };
    };
}
