#pragma once
#include "Collider.h"

namespace GameEngine {
	class CircleCollider :
		public Collider {
	public:
		CircleCollider(GameObject* owner)
			:Collider(owner)
		{}

		float radius = 25.f;
	};
}