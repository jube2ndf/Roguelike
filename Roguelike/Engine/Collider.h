#pragma once
#include "Component.h"

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

		bool isTrigger = false;
	};
}