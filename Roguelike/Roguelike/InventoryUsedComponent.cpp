#include "InventoryUsedComponent.h"
#include "Inventory.h"
#include <SFML/Window/Keyboard.hpp>

void Roguelike::InventoryUsedComponent::Update(float dt)
{
    auto* go = GetGameObject();
    auto* inventory = go->GetComponent<InventoryComponent>();
    if (!inventory || inventory->GetItems().size() == 0)
    {
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && 
        this->selectItem > 0)
    {
        this->selectItem--;
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) &&
        this->selectItem < inventory->GetItems().size() - 1)
    {
        this->selectItem++;
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
    {
        inventory->UseItem(this->selectItem);
        return;
    }
}
