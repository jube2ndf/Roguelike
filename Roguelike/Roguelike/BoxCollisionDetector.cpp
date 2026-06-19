#include "BoxCollisionDetector.h"
#include "CollisionLayers.h"
#include "ProjectileComponent.h"
#include <EventBus.h>

Roguelike::BoxCollisionAttackDetector::BoxCollisionAttackDetector(GameEngine::GameObject* owner)
    : BoxCollider(owner)
{
    this->isTrigger = true;
    this->layer = CollisionLayers::Projectile;
    this->mask =
        CollisionLayers::GameObject |
        CollisionLayers::DamageTaken |
        CollisionLayers::Destructible;
}

GameEngine::GameObject* Roguelike::BoxCollisionAttackDetector::Get()
{
    return this->target;
}

void Roguelike::BoxCollisionAttackDetector::OnTriggerEnter(Collider* other)
{
    ProjectileComponent* projectileComponent = 
        this->_owner->GetComponent<ProjectileComponent>();
    if (projectileComponent)
    {
        projectileComponent->OnHit(other->GetGameObject());
    }
      
}
