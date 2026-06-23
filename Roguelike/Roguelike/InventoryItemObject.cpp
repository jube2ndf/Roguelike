#include "InventoryItemObject.h"
#include "CollisionLayers.h"
#include "Inventory.h"

Roguelike::InventoryItemObject::InventoryItemObject(GameEngine::GameObject* owner, std::shared_ptr<IItem> item)
    : BoxCollider(owner), item(item)
{
    this->layer = CollisionLayers::GameItem;
    this->mask = CollisionLayers::PlayerBody;
    this->isTrigger = true;
}

void Roguelike::InventoryItemObject::OnTriggerEnter(Collider* other)
{
    if (auto invecntory = other->GetGameObject()->GetComponent<InventoryComponent>())
    {
        invecntory->AddItem(this->item);
        this->GetGameObject()->Destroy();
    }
}
