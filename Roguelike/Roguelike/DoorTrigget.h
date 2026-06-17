#pragma once
#include <ITriggerListener.h>
#include <Collider.h>
#include <BoxCollider.h>
namespace Roguelike
{
class DoorTrigget: public GameEngine::BoxCollider,
    public GameEngine::ITriggerListener
{
  public:
    DoorTrigget(GameEngine::GameObject* owner, std::string lvl) : BoxCollider(owner), door2LVL(lvl) {
        this->isTrigger = true;
    }
    void OnTriggerEnter(GameEngine::Collider* other) override;

  private:
    std::string door2LVL;
};

} // namespace Roguelike
