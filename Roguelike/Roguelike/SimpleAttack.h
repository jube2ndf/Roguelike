#pragma once
#include <Component.h>
#include "AttackComponent.h"
namespace Roguelike
{
class SimpleAttack : public GameEngine::Component
{
  public:
    static constexpr bool Unique = true;
    SimpleAttack(GameEngine::GameObject* owner);
    void Update(float dt) override;
    AttackComponent* used = nullptr;
};
} // namespace Roguelike
