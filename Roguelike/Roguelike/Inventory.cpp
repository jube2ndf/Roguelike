#include "Inventory.h"
#include <Logger.h>

void Roguelike::InventoryComponent::AddItem(std::shared_ptr<IItem> item, int count)
{
    for (auto& slot : slots)
    {
        if (slot.item->GetName() == item->GetName())
        {
            slot.count += count;
            LOG_INFO("Inventory", "Add " + slot.item->GetName());
            return;
        }
    }

    slots.push_back({item, count});
    LOG_INFO("Inventory", "Add " + item->GetName());
}

void Roguelike::InventoryComponent::RemoveItem(const std::string& name, int count)
{
    for (auto it = slots.begin(); it != slots.end();)
    {
        if (it->item->GetName() == name)
        {
            it->count -= count;

            if (it->count <= 0)
                it = slots.erase(it);
            else
                ++it;

            return;
        }
        else
        {
            ++it;
        }
    }
}

void Roguelike::InventoryComponent::UseItem(size_t index)
{
    if (index >= slots.size())
        return;

    auto& slot = slots[index];

    slot.item->Use(GetGameObject());

    slot.count--;
    LOG_INFO("Inventory", "Used " + slot.item->GetName());
    if (slot.count <= 0)
        slots.erase(slots.begin() + index);
}

const std::vector<Roguelike::InventoryComponent::InventorySlot>& Roguelike::InventoryComponent::GetItems() const
{
    return this->slots;
}
