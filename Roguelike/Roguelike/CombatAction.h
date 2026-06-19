#pragma once
#include <GameObject.h>
#include "CombatActionType.h"
#include "Damage.h"
namespace Roguelike {
	struct CombatAction
	{
		CombatActionType type = CombatActionType::Damage;

		GameEngine::GameObject* source = nullptr;
		GameEngine::GameObject* target = nullptr;

		float value = 0.f;
        Damage damage;
	};
}
