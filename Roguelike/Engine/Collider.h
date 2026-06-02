#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "GameObject.h"

namespace GameEngine {
	class Collider :
		public Component {
    public:
        static constexpr bool Unique = false;
        static constexpr bool Required = false;

        Collider(GameObject* owner) : Component(owner) {}
        virtual ~Collider() = default;

        virtual sf::Vector2f GetSize() const = 0;

        sf::Vector2f GetWorldCenter() const {
            auto transform = this->GetGameObject()->GetComponent<TransformComponent>();
            if (transform) {
                return transform->GetWorldPosition();
            }
            return { 0, 0 };
        }

        float GetWorldRotation() const {
            auto transform = this->GetGameObject()->GetComponent<TransformComponent>();
            if (transform) {
                return transform->GetWorldRotation();
            }
            return 0.f;
        }

        bool isTrigger = false;
		
	};
}