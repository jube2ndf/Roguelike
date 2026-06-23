#pragma once
#include <Component.h>
#include <GameObject.h>
#include <algorithm>
#include "StatsComponent.h"

namespace Roguelike {
	class HealthComponent:
		public GameEngine::Component
	{
	public:
		HealthComponent(GameEngine::GameObject* owner)
			:GameEngine::Component(owner)
		{
            currentHealth = this->_owner->GetComponent<StatsComponent>()->GetStat(StatType::MaxHealth);
		}

		void Update(float dt) override {
            if (currentHealth > GetMaxHealth())
				currentHealth = GetMaxHealth();
		}

		void TakeDamage(float damage)
		{
			currentHealth =
				std::max<float>(0.f,
					currentHealth - damage);
			if (!this->IsAlive()) {
				this->_owner->Destroy();
			}
		}

		float GetMaxHealth() const
		{
			return this->_owner->GetComponent<StatsComponent>()->GetStat(StatType::MaxHealth);
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
	protected:
		float currentHealth;
	};
}
