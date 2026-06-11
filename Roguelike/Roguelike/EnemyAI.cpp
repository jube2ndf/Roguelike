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
    auto* rb = GetGameObject()->GetComponent<GameEngine::Rigidbody>();

    if (!rb || !Ai)
        return;
    
    if (Ai->target == NULL) {
        rb->velocity = { 0.f, 0.f };
        return;
    }

    auto* selfTr = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
    auto* targetTr = Ai->target->GetComponent<GameEngine::TransformComponent>();
    auto* attack = GetGameObject()->GetComponent<AttackComponent>();

    if (!selfTr || !targetTr || !attack)
        return;

    sf::Vector2f toTarget =
    {
        targetTr->GetWorldPosition().x - selfTr->GetWorldPosition().x,
        targetTr->GetWorldPosition().y - selfTr->GetWorldPosition().y
    };

    float dist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    if (dist > 0.0001f)
        toTarget /= dist;

    float stopDistance =
        attack->distance +
        GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetHalfSize().x +
        Ai->target->GetComponent<GameEngine::BoxCollider>()->GetHalfSize().x;

    if (dist < stopDistance)
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
    auto* Ai = GetGameObject()->GetComponent<EnemyVision>();
    if (!attack || !Ai || !Ai->target)
        return;

    CombatAction action;
    action.source = GetGameObject();
    action.target = Ai->target;

    action.value = attack->damage;
    action.type = CombatActionType::Damage;

    GameEngine::EventBus::Emit(action);
}

