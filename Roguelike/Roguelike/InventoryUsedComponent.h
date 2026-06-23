#pragma once
#include <Component.h>
namespace Roguelike
{
class InventoryUsedComponent : public GameEngine::Component
{
  public:
    InventoryUsedComponent(GameEngine::GameObject* owner) : GameEngine::Component(owner) {}
    void Update(float dt) override;

  private:
    int selectItem = 0;
};
}
