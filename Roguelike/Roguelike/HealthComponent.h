#pragma once
#include <Component.h>
#include <GameObject.h>
#include <algorithm>

namespace Roguelike {
	class HealthComponent:
		public GameEngine::Component
	{
	public:
		HealthComponent(GameEngine::GameObject* owner, float baseHealth)
			:GameEngine::Component(owner),
			baseMaxHealth(baseHealth),
			bonusMaxHealth(0),
			currentHealth(baseHealth)
		{

		}

		void TakeDamage(float damage)
		{
			currentHealth =
				std::max<float>(0.f,
					currentHealth - damage);
		}

		float GetMaxHealth() const
		{
			return baseMaxHealth + bonusMaxHealth;
		}

		bool IsAlive() const
		{
			return currentHealth > 0.f;
		}

		void Heal(float amount)
		{
			currentHealth =
				std::min(currentHealth + amount,
					GetMaxHealth());
		}

		void TakeBonus(float bonus)
		{
			bonusMaxHealth += bonus;
		}

	protected:
		float baseMaxHealth;
		float bonusMaxHealth;
		float currentHealth;
	};
}
