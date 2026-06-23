#pragma once
#include <Component.h>
#include <GameObject.h>
#include "StatsComponent.h"

namespace Roguelike {
    class ArmorComponent :
        public GameEngine::Component
    {
    public:
        ArmorComponent(GameEngine::GameObject* owner)
            : Component(owner)
        {}

        float GetArmor() const
        {
            return this->_owner->GetComponent<StatsComponent>()->GetStat(StatType::Armor);
        }
    };
}
