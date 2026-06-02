#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "GameObject.h"

namespace GameEngine {
	class Collider :
		public Component {
	public:
		Collider(GameObject* owner) :
			Component(owner) 
		{}

		sf::Vector2f GetWorldPosition()
		{
			auto transform =
				this->GetGameObject()->GetComponent<TransformComponent>();

			return transform->GetWorldPosition();
		}

		virtual sf::Vector2f GetSize() const
		{
			return { 0.f, 0.f };
		}

		bool isTrigger = false;
	};
}