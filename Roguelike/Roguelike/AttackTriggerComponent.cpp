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
    
    attack->targets.erase(other->GetGameObject());
}
