#include "FastSwordProjectile.h"
#include "SimpleAttack.h"
#include <Logger.h>

void Roguelike::FastSwordProjectile::AddFastSwordProjectile(GameEngine::GameObject* owner)
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
    attackComponent->cooldown = 0.5f;
    attackComponent->type = WeaponType::FastSword;
    attack->used = attackComponent;
}

void Roguelike::FastSwordProjectile::RemoveFastSwordProjectile(GameEngine::GameObject* owner)
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
    if (attack->used->type != WeaponType::FastSword)
    {
        LOG_INFO("Attack", "Try remove FastSword, but SimpleAttack other WeaponType");
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
