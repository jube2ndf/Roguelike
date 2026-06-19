#pragma once
#include <ITriggerListener.h>
#include <BoxCollider.h>
#include <GameObject.h>
namespace Roguelike
{
class BoxCollisionAttackDetector : 
    public GameEngine::BoxCollider,   
    public GameEngine::ITriggerListener
{
  public:
    BoxCollisionAttackDetector(GameEngine::GameObject* owner);
    GameEngine::GameObject* Get();

    void OnTriggerEnter(Collider* other) override;
  private:
    GameEngine::GameObject* target = nullptr;
};
} // namespace Roguelike