#include "EnemyVision.h"
#include <TagComponent.h>
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <GameObject.h>
#include "AttackComponent.h"
#include <SpriteRenderer.h>
#include <math.h>

void Roguelike::EnemyVision::OnTriggerEnter(GameEngine::Collider* other)
{
    auto go = other->GetGameObject()->GetComponents<GameEngine::TagComponent>();
    for (auto iter : go) {
        if (iter->GetTag() == "Player")
        {
            target = other->GetGameObject();
        }
    }
}

void Roguelike::EnemyVision::OnTriggerStay(GameEngine::Collider* other)
{
    
}

void Roguelike::EnemyVision::OnTriggerExit(GameEngine::Collider* other)
{
    auto go = other->GetGameObject();

    if (go == target)
    {
        target = nullptr;
    }
}
