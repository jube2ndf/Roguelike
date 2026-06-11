#include "EnemyAI.h"
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <EventBus.h>
#include "CombatAction.h"
#include "AttackComponent.h"
#include "EntityVision.h"
#include <unordered_set>


void Roguelike::EnemyAI::Update(float dt)
{
    auto* Ai = GetGameObject()->GetComponent<EntityVision>();
    auto* rb = GetGameObject()->GetComponent<GameEngine::Rigidbody>();

    if (!rb || !Ai)
        return;
    
    if (Ai->targets.size() == 0) {
        rb->velocity = { 0.f, 0.f };
        return;
    }

    auto* selfTr = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
    auto* attack = GetGameObject()->GetComponent<AttackComponent>();

    if (!selfTr || !attack)
        return;

    
    float closestDist = std::numeric_limits<float>::max();

    for (auto* obj : Ai->targets)
    {
        auto* tr =
            obj->GetComponent<GameEngine::TransformComponent>();

        if (!tr)
            continue;

        sf::Vector2f d =
        {
            tr->GetWorldPosition().x - selfTr->GetWorldPosition().x,
            tr->GetWorldPosition().y - selfTr->GetWorldPosition().y
        };

        float dist = d.x * d.x + d.y * d.y;

        if (dist < closestDist)
        {
            closestDist = dist;
            closest = obj;
        }
    }

    if (!closest)
    {
        rb->velocity = { 0.f, 0.f };
        return;
    }
    auto* targetTr = closest->GetComponent<GameEngine::TransformComponent>();
    if (!targetTr) {
        rb->velocity = { 0.f, 0.f };
        return;
    }
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
        GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetRadius() +
        closest->GetComponent<GameEngine::BoxCollider>()->GetRadius();

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
    auto* Ai = GetGameObject()->GetComponent<EntityVision>();
    if (!attack || !Ai || !closest)
        return;

    CombatAction action;
    action.source = GetGameObject();
    action.target = closest;

    action.value = attack->damage;
    action.type = CombatActionType::Damage;

    GameEngine::EventBus::Emit(action);
}

