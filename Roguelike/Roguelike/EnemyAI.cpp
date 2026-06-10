#include "EnemyAI.h"
#include <TagComponent.h>
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <GameObject.h>
#include "AttackComponent.h"
#include <SpriteRenderer.h>

void Roguelike::EnemyAI::OnTriggerEnter(GameEngine::Collider* other)
{
    auto go = other->GetGameObject()->GetComponents<GameEngine::TagComponent>();
    for (auto iter : go) {
        if (iter->GetTag() == "Player")
        {
            target = other->GetGameObject();
        }
    }
}

void Roguelike::EnemyAI::OnTriggerStay(GameEngine::Collider* other)
{
    auto rb = GetGameObject()->GetComponent<GameEngine::Rigidbody>();
    auto tr = GetGameObject()->GetComponent<GameEngine::TransformComponent>();
    if (!rb || !tr)
        return;

    if (!target)
    {
        rb->velocity = { 0.f, 0.f };
        return;
    }

    auto targetTr =
        target->GetComponent<GameEngine::TransformComponent>();

    if (!targetTr)
    {
        rb->velocity = { 0.f, 0.f };
        return;
    }

    sf::Vector2f dir =
    {
        targetTr->GetWorldPosition().x - tr->GetWorldPosition().x,
        targetTr->GetWorldPosition().y - tr->GetWorldPosition().y
    };

    float len =
        std::sqrt(dir.x * dir.x + dir.y * dir.y);
    float stopLen = 0.f;
    auto colliders = GetGameObject()->GetComponents<GameEngine::Collider>();
    for (auto* iter : colliders) {
        if (!iter->isTrigger &&
                (
                    stopLen < iter->GetSize().x / 2 ||
                    stopLen < iter->GetSize().y / 2
                )
            )
        {
            stopLen = iter->GetSize().y < iter->GetSize().x ? iter->GetSize().x / 2: iter->GetSize().x / 2;
        }
    }

    auto attackComponent = GetGameObject()->GetComponent<AttackComponent>();
    if (attackComponent) {
        stopLen += attackComponent->distance;
    }

    if (len <= stopLen)
    {
        rb->velocity = { 0.f, 0.f };
        return;
    }

    if (len > 0.001f)
        dir /= len;

    rb->velocity = dir * speed;
}

void Roguelike::EnemyAI::OnTriggerExit(GameEngine::Collider* other)
{
    auto go = other->GetGameObject();

    if (go == target)
    {
        target = nullptr;
    }
}
