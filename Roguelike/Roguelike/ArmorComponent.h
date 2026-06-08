#pragma once
#include <Component.h>
#include <GameObject.h>

namespace Roguelike {
    class ArmorComponent :
        public GameEngine::Component
    {
    public:
        ArmorComponent(GameEngine::GameObject* owner)
            : Component(owner)
        {}
        float baseArmor = 0.f;
        float bonusArmor = 0.f;

        float GetArmor() const
        {
            return baseArmor + bonusArmor;
        }
    };
}
