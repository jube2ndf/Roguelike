#pragma once
#include <Component.h>
#include <GameObject.h>

namespace Roguelike {
	class EnemyAI:
		public GameEngine::Component
	{
	public:
		EnemyAI(GameEngine::GameObject* owner) :
			Component(owner) {
		}
		float speed = 120.f;

		void Update(float dt) override;
	private:
		GameEngine::GameObject* closest = nullptr;
		void Attack();
	};
}
