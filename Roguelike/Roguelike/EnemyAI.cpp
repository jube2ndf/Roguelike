#include "EnemyAI.h"
#include <TagComponent.h>
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <GameObject.h>

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

    sf::Vector2f dir =
    {
        targetTr->GetWorldPosition().x - tr->GetWorldPosition().x,
        targetTr->GetWorldPosition().y - tr->GetWorldPosition().y
    };

    float len =
        std::sqrt(dir.x * dir.x + dir.y * dir.y);

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
