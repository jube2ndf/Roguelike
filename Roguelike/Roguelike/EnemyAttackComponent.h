#pragma once
#include <BoxCollider.h>
#include <ITriggerListener.h>
#include "AttackComponent.h"
#include <SpriteRenderer.h>

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
            auto colliders = owner->GetComponents<GameEngine::Collider>();

            if (attack) {
                this->size = sf::Vector2f(
                    attack->distance,
                    attack->distance
                );
            }
            float add = 0;
            for (auto* iter : colliders) {
                if (!iter->isTrigger) {
                    float dist = iter->GetSize().length();
                    if (dist > add) {
                        add = dist;
                    }
                }
            }
            this->size.x += add;
            this->size.y += add;
        }

        void OnTriggerStay(
            GameEngine::Collider* other) override;
    };
}