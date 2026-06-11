#include "EntityVision.h"
#include <TagComponent.h>
#include <TransformComponent.h>
#include <Rigidbody.h>
#include <GameObject.h>
#include "AttackComponent.h"
#include <SpriteRenderer.h>
#include <math.h>
#include <Logger.h>

void Roguelike::EntityVision::OnTriggerEnter(GameEngine::Collider* other)
{
    auto go = other->GetGameObject()->GetComponents<GameEngine::TagComponent>();
    for (auto iter : go) {
        if (iter->GetTag() == "Player")
        {
            if (this->GetGameObject() == other->GetGameObject())
                return;

            if (targets.find(other->GetGameObject()) == targets.end())
                targets.insert(other->GetGameObject());
        }
    }
}

void Roguelike::EntityVision::OnTriggerStay(GameEngine::Collider* other)
{
    
}

void Roguelike::EntityVision::OnTriggerExit(GameEngine::Collider* other)
{
    auto go = other->GetGameObject();
    
    if (this->GetGameObject() == other->GetGameObject())
        return;

    targets.erase(other->GetGameObject());
}
