#pragma once
#include <Component.h>
#include <SFML/System/Vector2.hpp>
#include "Damage.h"
namespace Roguelike
{
class ProjectileComponent: public GameEngine::Component
{
  public:
    ProjectileComponent(GameEngine::GameObject* owner,
                        float damage,
                        float critChance,
                        float critMultiplier,
                        DamageType type,
                        GameEngine::GameObject* source);

    virtual void Start();
    void Update(float dt) override;
    virtual void OnHit(GameEngine::GameObject* other);

    sf::Vector2f direction;
    float speed = 300.f;
    Damage damage;
    float lifeTime = 10.f;


    GameEngine::GameObject* source = nullptr;
};
} // namespace Roguelike
