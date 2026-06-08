#pragma once
#include "CombatAction.h"
#include <IGameLayer.h>
namespace Roguelike {
	class CombatSystem :
		public GameEngine::IGameLayer
	{
	public:
		CombatSystem() = default;
		void QueueAction(
			const CombatAction& action);

		void Update(float dt) override;

	private:

		std::vector<CombatAction> _actions;

		void ApplyDamage(
			const CombatAction& action);

		void ApplyHeal(
			const CombatAction& action);
	};
}
