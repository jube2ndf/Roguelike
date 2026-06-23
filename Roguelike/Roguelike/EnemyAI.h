#pragma once
#include <Component.h>
#include <GameObject.h>
#include "SimpleAttack.h"

namespace Roguelike {
	class EnemyAI:
		public SimpleAttack
	{
	public:
		EnemyAI(GameEngine::GameObject* owner) :
			SimpleAttack(owner) {
		}

		void Update(float dt) override;
	private:
		GameEngine::GameObject* closest = nullptr;
		void Attack();
	};
}
