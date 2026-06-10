#pragma once
#include <BoxCollider.h>
#include <ITriggerListener.h>
#include <GameObject.h>
#include <Collider.h>

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
            this->size = { 100.f, 100.f };
        }

        void OnTriggerEnter(GameEngine::Collider* other) override;
        void OnTriggerExit(GameEngine::Collider* other) override;
    };
}
