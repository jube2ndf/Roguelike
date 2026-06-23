#pragma once
#include <GameObject.h>
namespace Roguelike
{
class IEffect
{
  public:
    virtual ~IEffect() = default;

    virtual void OnApply(GameEngine::GameObject* target) {}
    virtual void OnUpdate(GameEngine::GameObject* target, float dt) {}
    virtual void OnRemove(GameEngine::GameObject* target) {}

    virtual bool IsFinished() const = 0;
};
}