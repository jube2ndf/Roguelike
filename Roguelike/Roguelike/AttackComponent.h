#pragma once
#include <Component.h>
#include <algorithm>
#include "WeaponFactory.h"
#include "WeaponType.h"
namespace Roguelike
{
    class AttackComponent : public GameEngine::Component
    {
    public:
        AttackComponent(GameEngine::GameObject* owner)
          : AttackComponent(owner, WeaponType::FastSword)
      {

        }
        AttackComponent(GameEngine::GameObject* owner, WeaponType type)
            : Component(owner)
        {
            this->type = type;
            if (WeaponFactory::culDown.contains(type))
                this->cooldown = WeaponFactory::culDown.find(type)->second;
        }

        WeaponType type;

        float cooldown = 5.f;

        float timer = 0.f;

        void Update(float dt) override
        {
            if (timer > 0.f)
                timer = std::max<float>(0, timer - dt);
        }

        bool CanAttack() const
        {
            return timer <= 0.f;
        }

        void ResetCooldown()
        {
            timer = cooldown;
        }
    };
}