#include "CombatSystem.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include <Logger.h>

void Roguelike::CombatSystem::QueueAction(const CombatAction& action)
{
	this->_actions.push_back(action);
}

void Roguelike::CombatSystem::Update(float dt)
{
    for (auto& action : _actions)
    {
        switch (action.type)
        {
        case CombatActionType::Damage:
            LOG_INFO("Attack",
                "source: " + std::to_string(reinterpret_cast<uintptr_t>(action.source)) +
                "; target: " + std::to_string(reinterpret_cast<uintptr_t>(action.target)) + "; value: " 
                + std::to_string(action.value));
            ApplyDamage(action);
            break;

        case CombatActionType::Heal:
            ApplyHeal(action);
            break;
        }
    }

    _actions.clear();
}


void Roguelike::CombatSystem::ApplyDamage(
    const CombatAction& action)
{
    if (!action.target)
        return;

    auto hp = action.target->GetComponent<HealthComponent>();
    if (!hp)
        return;

    float finalDamage = action.damage.base;

    if (action.damage.critChance > 0.f)
    {
        float roll = rand() % 100 / 100.f;
        if (roll < action.damage.critChance)
            finalDamage *= action.damage.critMultiplier;
    }

    if (auto armor = action.target->GetComponent<ArmorComponent>())
    {
        float a = armor->GetArmor();
        finalDamage *= (100.f / (100.f + a));
    }

    hp->TakeDamage(finalDamage);
}

void Roguelike::CombatSystem::ApplyHeal(
    const CombatAction& action)
{
    if (!action.target)
        return;

    auto hp =
        action.target
        ->GetComponent<HealthComponent>();

    if (!hp)
        return;

    hp->Heal(action.value);
}
