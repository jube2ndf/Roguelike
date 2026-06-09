#include "PlayerAttackComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include "CombatAction.h"
#include "HealthComponent.h"
#include <EventBus.h>
#include <Logger.h>

void Roguelike::PlayerAttackComponent::Update(float dt)
{
    if (timer >= 0.f)
    {
        timer = std::max<float>(0, timer - dt);
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        return;

    if (!this->CanAttack())
    {
        LOG_INFO("PressAttack",
            "Cooldown wait: " + std::to_string(this->timer));
        return;
    }

    for (auto* target : this->targets)
    {
        if (!target)
            continue;
        if (!target->GetComponent<HealthComponent>()) {
            continue;
        }
        CombatAction action;
        action.type = CombatActionType::Damage;
        action.source = GetGameObject();
        action.target = target;
        action.value = this->damage;
        LOG_INFO("PlayerPressAttack",
            "target: " + std::to_string(reinterpret_cast<uintptr_t>(action.target)));
        GameEngine::EventBus::Emit(action);
    }

    this->ResetCooldown();
}
