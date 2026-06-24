#include "ProjectileComponent.h"
#include <Rigidbody.h>
#include <GameObject.h>
#include <EventBus.h>
#include "CombatAction.h"

Roguelike::ProjectileComponent::ProjectileComponent(
    GameEngine::GameObject* owner, 
    float damage,
    float critChance,
    float critMultiplier,
    Damage::Context type,
    GameEngine::GameObject* source
)
    : Component(owner)
{
    this->damage.base = damage;
    this->damage.critChance = 1;
    this->damage.critMultiplier = 1;
    this->damage.context = {DamageType::Physical};
    this->damage.source = owner;
    this->source = source;
}

void Roguelike::ProjectileComponent::Start()
{
    auto rb = this->_owner->GetComponent<GameEngine::Rigidbody>();

    if (rb)
    {
        rb->velocity = direction * speed;
    }
}

void Roguelike::ProjectileComponent::Update(float dt)
{
    lifeTime -= dt;

    if (lifeTime <= 0.f || !this->source)
        this->_owner->Destroy();
}

void Roguelike::ProjectileComponent::OnHit(GameEngine::GameObject* other)
{
    if (other == this->source)
        return;
    this->damage.target = other;
    
    CombatAction action;
    action.type = CombatActionType::Damage;
    action.source = this->_owner;
    action.target = other;
    action.damage = this->damage;
    GameEngine::EventBus::Emit(action);
    this->_owner->Destroy();
}
