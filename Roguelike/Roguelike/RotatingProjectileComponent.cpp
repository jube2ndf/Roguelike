#include "RotatingProjectileComponent.h"
#include "Damage.h"
#include "CombatAction.h"
#include <EventBus.h>

Roguelike::RotatingProjectileComponent::RotatingProjectileComponent(GameEngine::GameObject* owner,
                                                                    float damage,
                                                                    float critChance,
                                                                    float critMultiplier,
                                                                    Damage::Context data,
                                                                    GameEngine::GameObject* source): 
    ProjectileComponent(
        owner,
        damage, 
        critChance,
        critMultiplier,
        data,
        source
       )
{
    lifeTime = 5.f;
}

void Roguelike::RotatingProjectileComponent::Update(float dt)
{
    lifeTime -= dt;

    if (lifeTime <= 0.f)
    {
        _owner->Destroy();
        return;
    }

    if (!this->source)
        return;

    auto centerTransform =
        this->source->GetComponent<GameEngine::TransformComponent>();

    auto myTransform =
        _owner->GetComponent<GameEngine::TransformComponent>();

    if (!centerTransform || !myTransform)
        return;

    angle += angularSpeed * dt;

    sf::Vector2f centerPos =
        centerTransform->GetWorldPosition();

    sf::Vector2f pos{
        centerPos.x + std::cos(angle) * radius,
        centerPos.y + std::sin(angle) * radius};

    myTransform->SetWorldPosition(pos);

    float current = myTransform->GetWorldRotation();

    float target = angle * 180.f / 3.14159265f;

    float delta = target - current;

    while (delta > 180.f)
        delta -= 360.f;
    while (delta < -180.f)
        delta += 360.f;

    float rotateSpeed = 360.f;

    myTransform->RotateBy(
        std::clamp(
            delta,
            -rotateSpeed * dt,
            rotateSpeed * dt));
}

void Roguelike::RotatingProjectileComponent::OnHit(GameEngine::GameObject* other)
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
    //this->_owner->Destroy();
}
