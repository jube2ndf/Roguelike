#include "HealthPotion.h"
#include "HealthComponent.h"

void Roguelike::HealthPotion::Use(GameEngine::GameObject* user)
{
    if (!user)
        return;

    auto health =
        user->GetComponent<HealthComponent>();

    if (!health)
        return;

    health->Heal(healAmount);
}

std::string Roguelike::HealthPotion::GetName() const
{
    return this->name;
}
