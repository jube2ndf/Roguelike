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
		GameEngine::GameObject* target = nullptr;

		void Update(float dt) override;
	private:
		void Attack();
	};
}
