#pragma once
#include "Component.h"

namespace GameEngine {
	class Collider :
		public Component {
	public:
		Collider(GameObject* owner) :
			Component(owner) 
		{}

		bool isTrigger = false;
	};
}