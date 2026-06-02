#pragma once
#include "Collider.h"

namespace GameEngine {
	class ENGINE_API CircleCollider :
		public Collider {
	public:
		CircleCollider(GameObject* owner)
			:Collider(owner)
		{}
		sf::Vector2f GetSize() const override
		{
			return { radius * 2.f, radius * 2.f };
		}
		float radius = 25.f;

	};
}