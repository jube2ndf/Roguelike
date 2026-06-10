#include "EnemyAI.h"
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <EventBus.h>
#include "CombatAction.h"
#include "AttackComponent.h"
#include "EnemyVision.h"


void Roguelike::EnemyAI::Update(float dt)
{
    auto* Ai = GetGameObject()->GetComponent<EnemyVision>();
    if (Ai && Ai->target) {
        target = Ai->target;
    }
    else {
        return;
    }

    auto* rb = GetGameObject()->GetComponent<GameEngine::Rigidbody>();
    if (!target)
    {
        rb->velocity = { 0.f, 0.f };
        return;
    }

    auto* selfTr = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
    auto* targetTr = target->GetComponent<GameEngine::TransformComponent>();
    auto* attack = GetGameObject()->GetComponent<AttackComponent>();

    if (!selfTr || !targetTr || !rb || !attack)
        return;

    sf::Vector2f toTarget =
    {
        targetTr->GetWorldPosition().x - selfTr->GetWorldPosition().x,
        targetTr->GetWorldPosition().y - selfTr->GetWorldPosition().y
    };

    float dist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (dist > 0.0001f)
        toTarget /= dist;

    if (dist <= attack->distance)
    {
        rb->velocity = { 0.f, 0.f };

        if (attack->CanAttack())
        {
            Attack();
            attack->ResetCooldown();
        }

        return;
    }

    rb->velocity = toTarget * speed;
}

void Roguelike::EnemyAI::Attack()
{
    auto* attack = GetGameObject()->GetComponent<AttackComponent>();

    if (!attack || !target)
        return;

    CombatAction action;
    action.source = GetGameObject();
    action.target = target;

    action.value = attack->damage;
    action.type = CombatActionType::Damage;

    GameEngine::EventBus::Emit(action);
}

