#pragma once
#include "Collider.h"

namespace GameEngine {
	class CircleCollider :
		public Collider {
		CircleCollider(GameObject* owner)
			:Collider(owner)
		{}

		float radius = 25.f;
	};
}