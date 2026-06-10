#pragma once
#include <BoxCollider.h>
#include <ITriggerListener.h>
#include <GameObject.h>
#include <Collider.h>
#include "AttackComponent.h"

namespace Roguelike {
    class AttackTriggerComponent :
        public GameEngine::BoxCollider,
        public GameEngine::ITriggerListener
    {
    public:
        AttackTriggerComponent(GameEngine::GameObject* owner)
            :BoxCollider(owner) 
        {
            this->isTrigger = true;
            float ownerRadius = 0.f;

            auto colliders =
                owner->GetComponents<GameEngine::Collider>();

            for (auto* collider : colliders)
            {
                if (collider->isTrigger)
                    continue;

                ownerRadius = std::max(
                    ownerRadius,
                    collider->GetSize().length() * 0.5f);
            }

            auto attack =
                owner->GetComponent<AttackComponent>();

            float radius = ownerRadius +
                (attack ? attack->distance : 0.f);

            this->size.x = radius * 2.f;
            this->size.y = radius * 2.f;
        }

        void OnTriggerEnter(GameEngine::Collider* other) override;
        void OnTriggerExit(GameEngine::Collider* other) override;
    };
}
