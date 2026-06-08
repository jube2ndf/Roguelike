#include "AttackTriggerComponent.h"
#include "PlayerAttackComponent.h"
#include <Logger.h>

void Roguelike::AttackTriggerComponent::OnTriggerEnter(GameEngine::Collider* other)
{
    auto attack =
        GetGameObject()->GetComponent<Roguelike::PlayerAttackComponent>();

    if (!attack)
        return;

    if (this->GetGameObject() == other->GetGameObject())
        return;

    LOG_INFO("PlayerAttack",
        "Owmer: " + std::to_string(reinterpret_cast<uintptr_t>(this->GetGameObject())) +
        "; Add target: " + std::to_string(reinterpret_cast<uintptr_t>(other->GetGameObject())));
    if(attack->targets.find(other->GetGameObject()) == attack->targets.end())
        attack->targets.insert(other->GetGameObject());
}

void Roguelike::AttackTriggerComponent::OnTriggerExit(GameEngine::Collider * other)
{
    auto attack =
        GetGameObject()->GetComponent<Roguelike::PlayerAttackComponent>();

    if (!attack)
        return;

    if (this->GetGameObject() == other->GetGameObject())
        return;
    LOG_INFO("PlayerAttack",
        "Owmer: " + std::to_string(reinterpret_cast<uintptr_t>(this->GetGameObject())) +
        "; Remove target: " + std::to_string(reinterpret_cast<uintptr_t>(other->GetGameObject())));
    attack->targets.erase(other->GetGameObject());
}
