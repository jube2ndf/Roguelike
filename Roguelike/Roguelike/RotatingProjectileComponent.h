#pragma once
#include "ProjectileComponent.h"
namespace Roguelike
{
class RotatingProjectileComponent : public ProjectileComponent
{
  public:
    RotatingProjectileComponent(
        GameEngine::GameObject* owner,  
        float damage,   
        float critChance,  
        float critMultiplier,  
        Damage::Context data,
        GameEngine::GameObject* source
        );

    float radius = 50.f;
    float angle = 0.f;
    float angularSpeed = 5.f;

    void Start() override {};
    void Update(float dt) override;
    void OnHit(GameEngine::GameObject* other) override;
};
} // namespace Roguelike
