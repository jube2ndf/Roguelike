#include "EnemyAI.h"
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <EventBus.h>
#include "CombatAction.h"
#include "AttackComponent.h"
#include "EntityVision.h"
#include <unordered_set>
#include "Math.h"


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

    float desiredDistance =
        GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetRadius() * 2 +
        closest->GetComponent<GameEngine::BoxCollider>()->GetRadius() * 2;

    float distanceTolerance = 16.f;

    // Нормализованный вектор к цели уже есть в toTarget

    // Перпендикуляр к цели
    sf::Vector2f side =
        {
            -toTarget.y,
            toTarget.x};

    // направление обхода: 1 или -1
    side *= (std::rand() % 2 == 0)
                ? 1.f
                : -1.f;

    sf::Vector2f moveDir{0.f, 0.f};

    if (dist > desiredDistance + distanceTolerance)
    {
        // Подходим к цели
        moveDir = toTarget;
    }
    else if (dist < desiredDistance - distanceTolerance)
    {
        // Отходим от цели
        moveDir = -toTarget;
    }
    else
    {
        // Находимся на нужной дистанции —
        // двигаемся по окружности вокруг игрока
        moveDir = side;
    }

    rb->velocity = moveDir * speed;

    if (attack->CanAttack())
    {
        Attack();
        attack->ResetCooldown();
    }
}

void Roguelike::EnemyAI::Attack()
{
    auto* attack = GetGameObject()->GetComponent<AttackComponent>();
    auto* Ai = GetGameObject()->GetComponent<EntityVision>();
    if (!attack || !Ai || !closest)
        return;

    auto transform =
        this->GetGameObject()->GetComponent<GameEngine::TransformComponent>();
    auto transformTarget =
        this->closest->GetComponent<GameEngine::TransformComponent>();
    sf::Vector2f enemy =
        transform->GetWorldPosition();
    auto direction = Math::Normalize(transformTarget->GetWorldPosition() - enemy);
    if (attack)
    {
        CreateWeapon dto;
        dto.data.direction = direction;
        dto.data.position = enemy;
        dto.type = attack->type;
        dto.source = this->GetGameObject();
        GameEngine::EventBus::Emit(dto);
        this->used->ResetCooldown();
    }
}

