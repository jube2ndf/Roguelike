#include "CombatSystem.h"
#include "HealthComponent.h"
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

    auto hp =
        action.target
        ->GetComponent<HealthComponent>();

    if (!hp)
        return;

    hp->TakeDamage(action.value);
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
