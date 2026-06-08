#pragma once
#include <Component.h>

namespace Roguelike {
    class ArmorComponent :
        public GameEngine::Component
    {
    public:
        float baseArmor = 0.f;
        float bonusArmor = 0.f;

        float GetArmor() const
        {
            return baseArmor + bonusArmor;
        }
    };
}
