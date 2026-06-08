#include "EnemyAttackComponent.h"
#include <TagComponent.h>
#include <EventBus.h>
#include "AttackComponent.h"
#include "CombatAction.h"

void Roguelike::EnemyAttackComponent::OnTriggerStay(GameEngine::Collider* other)
{
    auto attack =
        GetGameObject()
        ->GetComponent<AttackComponent>();

    if (!attack)
        return;

    if (!attack->CanAttack())
        return;

    auto tags =
        other->GetGameObject()
        ->GetComponents<GameEngine::TagComponent>();

    bool isPlayer = false;

    for (auto tag : tags)
    {
        if (tag->GetTag() == "Player")
        {
            isPlayer = true;
            break;
        }
    }

    if (!isPlayer)
        return;

    CombatAction action{
        CombatActionType::Damage,
        GetGameObject(),
        other->GetGameObject(),
        attack->damage
    };

    attack->ResetCooldown();

    GameEngine::EventBus::Emit(action);
}
