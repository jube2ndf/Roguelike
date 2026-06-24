#include "EnemyAI.h"
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <EventBus.h>
#include "CombatAction.h"
#include "AttackComponent.h"
#include "EntityVision.h"
#include <unordered_set>
#include "Math.h"
#include "StatsComponent.h"
#include <TagComponent.h>
#include "EventDieBoss.h"

void Roguelike::EnemyAI::Update(float dt)
{
    if (!_owner->IsAlive())
    {
        for (auto iter : _owner->GetComponents<GameEngine::TagComponent>())
        {
            if (iter->GetTag() == "Boss")
            {
                BossDiedEvent dto;
                dto.boss = _owner;
                GameEngine::EventBus::Emit(dto);
                return;
            }
        }
    }

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

    float desiredDistance =
        GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetRadius() * 2 +
        closest->GetComponent<GameEngine::BoxCollider>()->GetRadius() * 2;

    float distanceTolerance = 16.f;

    sf::Vector2f side =
        {
            -toTarget.y,
            toTarget.x};

    side *= (std::rand() % 2 == 0)
                ? 1.f
                : -1.f;

    sf::Vector2f moveDir{0.f, 0.f};

    if (dist > desiredDistance + distanceTolerance)
    {
        moveDir = toTarget;
    }
    else if (dist < desiredDistance - distanceTolerance)
    {
        moveDir = -toTarget;
    }
    else
    {
        moveDir = side;
    }

    rb->velocity = moveDir * this->_owner->GetComponent<StatsComponent>()->GetStat(StatType::MoveSpeed);
    ;

    if (attack->CanAttack())
    {
        Attack();
        attack->ResetCooldown();
    }
}

void Roguelike::EnemyAI::Attack()
{
    auto attack = GetGameObject()->GetComponents<AttackComponent>();
    auto* Ai = GetGameObject()->GetComponent<EntityVision>();
    if (attack.size() == 0 || !Ai || !closest)
        return;
    for (auto iter : attack)
    {
        auto transform =
            this->GetGameObject()->GetComponent<GameEngine::TransformComponent>();
        auto transformTarget =
            this->closest->GetComponent<GameEngine::TransformComponent>();
        sf::Vector2f enemy =
            transform->GetWorldPosition();
        auto direction = Math::Normalize(transformTarget->GetWorldPosition() - enemy);

        CreateWeapon dto;
        dto.data.direction = direction;
        dto.data.position = enemy;
        dto.type = iter->type;
        dto.source = this->GetGameObject();
        GameEngine::EventBus::Emit(dto);
        this->used->ResetCooldown();
    }
}

