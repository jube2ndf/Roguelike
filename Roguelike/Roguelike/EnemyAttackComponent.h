#pragma once
#include <BoxCollider.h>
#include <ITriggerListener.h>
#include "AttackComponent.h"

namespace Roguelike {
    class EnemyAttackComponent :
        public GameEngine::BoxCollider,
        public GameEngine::ITriggerListener
    {
    public:

        EnemyAttackComponent(
            GameEngine::GameObject* owner)
            : BoxCollider(owner)
        {
            this->isTrigger = true;

            auto attack = owner->GetComponent<AttackComponent>();

            if (attack) {
                this->size = sf::Vector2f(
                    attack->distance,
                    attack->distance
                );
            }
        }

        void OnTriggerStay(
            GameEngine::Collider* other) override;
    };
}