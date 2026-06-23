#pragma once
#include <ITriggerListener.h>
#include <BoxCollider.h>
#include "IItem.h"
namespace Roguelike
{
class InventoryItemObject: public GameEngine::BoxCollider, public GameEngine::ITriggerListener
{
  public:
    InventoryItemObject(GameEngine::GameObject* owner, std::shared_ptr<IItem> item);

	virtual void OnTriggerEnter(Collider* other);

	std::shared_ptr<IItem> item;
};
} // namespace Roguelike
