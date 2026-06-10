#pragma once
#include <Component.h>
#include <ITriggerListener.h>
#include <GameObject.h>
#include <BoxCollider.h>
namespace Roguelike {
    class EnemyVision :
        public GameEngine::BoxCollider,
        public GameEngine::ITriggerListener
    {
    public:
        EnemyVision(GameEngine::GameObject* owner):
            GameEngine::BoxCollider(owner) {
            this->isTrigger = true;
            this->size = { 500.f, 500.f };
        }
        GameEngine::GameObject* target = nullptr;


        void OnTriggerEnter(GameEngine::Collider* other) override;
        void OnTriggerStay(GameEngine::Collider* other) override;
        void OnTriggerExit(GameEngine::Collider* other) override;
    };
}
