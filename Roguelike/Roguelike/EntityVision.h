#pragma once
#include <Component.h>
#include <ITriggerListener.h>
#include <GameObject.h>
#include <BoxCollider.h>
#include <unordered_set>

namespace Roguelike {
    class EntityVision :
        public GameEngine::BoxCollider,
        public GameEngine::ITriggerListener
    {
    public:
        EntityVision(GameEngine::GameObject* owner):
            GameEngine::BoxCollider(owner) {
            this->isTrigger = true;
            this->size = { 500.f, 500.f };
        }
        std::unordered_set<GameEngine::GameObject*> targets;


        void OnTriggerEnter(GameEngine::Collider* other) override;
        void OnTriggerStay(GameEngine::Collider* other) override;
        void OnTriggerExit(GameEngine::Collider* other) override;
    };
}
