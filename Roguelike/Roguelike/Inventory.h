#pragma once
#include <Component.h>
#include "IItem.h"
namespace Roguelike
{
class InventoryComponent : public GameEngine::Component
{
  public:
    struct InventorySlot
    {
        std::shared_ptr<IItem> item;
        int count = 0;
    };

    InventoryComponent(GameEngine::GameObject* owner)
        : Component(owner)
    {

    }

    void AddItem(std::shared_ptr<IItem> item, int count = 1);

    void RemoveItem(const std::string& name, int count = 1);

    void UseItem(size_t index);

    const std::vector<InventorySlot>& GetItems() const;

  private:
    std::vector<InventorySlot> slots;
};
} // namespace Roguelike
