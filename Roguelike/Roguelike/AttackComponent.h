#pragma once
#include <Component.h>

namespace Roguelike
{
    class AttackComponent : public GameEngine::Component
    {
    public:
        AttackComponent(GameEngine::GameObject* owner)
            : Component(owner)
        {}
        float distance = 20.f;

        float damage = 10.f;

        float cooldown = 1.f;

        float timer = 10.f;

        void Update(float dt) override
        {
            if (timer > 0.f)
                timer -= dt;
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