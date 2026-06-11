#pragma once
#include <BoxCollider.h>
#include <ITriggerListener.h>
#include "AttackComponent.h"
#include <unordered_set>

namespace Roguelike {
	class PlayerAttackComponent:
		public AttackComponent
	{

	public:
		PlayerAttackComponent(GameEngine::GameObject* owner)
			: AttackComponent(owner)
		{
			
		}

		void Update(float dt) override;

	};
}
