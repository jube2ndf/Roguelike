#include "SwordProjectile.h"
#include "SimpleAttack.h"
#include <Logger.h>

void Roguelike::SwordProjectile::AddSwordProjectile(GameEngine::GameObject* owner, WeaponType type)
{
    SimpleAttack* attack = owner->GetComponent<SimpleAttack>();
    if (!attack)
    {
        LOG_WARN("Attack", "Not add FastSwordProjectile(not SimpleAttack component)");
        return;
    }
    if (attack->used)
    {
        LOG_WARN("Attack", "SimpleAttack is not empty(Object have AttackComponent)");
        return;
    }

    auto attackComponent = owner->AddComponent<AttackComponent>();
    attackComponent->cooldown = WeaponFactory::culDown.find(type)->second;
    attackComponent->type = type;
    attack->used = attackComponent;
}

void Roguelike::SwordProjectile::RemoveSwordProjectile(GameEngine::GameObject* owner, WeaponType type)
{
    SimpleAttack* attack = owner->GetComponent<SimpleAttack>();
    if (!attack)
    {
        LOG_WARN("Attack", "Not remove FastSwordProjectile(not SimpleAttack component)");
        return;
    }

    if (!attack->used)
    {
        LOG_WARN("Attack", "SimpleAttack is empty");
        return;
    }

    auto attackComponents = owner->GetComponents<AttackComponent>();
    for (auto iter : attackComponents)
    {
        if (attack->used == iter)
        {
            owner->RemoveComponent<AttackComponent>(iter);
            return;
        }
    }
}

void Roguelike::SwordProjectile::AddRotatingProjectile(GameEngine::GameObject* owner, WeaponType type)
{
    auto attackComponent = owner->AddComponent<AttackComponent>();
    attackComponent->cooldown = WeaponFactory::culDown.find(type)->second;
    attackComponent->type = type;
}
