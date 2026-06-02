#pragma once
#include <Component.h>
#include <ITriggerListener.h>
#include <GameObject.h>
#include <BoxCollider.h>
namespace Roguelike {
    class EnemyAI :
        public GameEngine::BoxCollider,
        public GameEngine::ITriggerListener
    {
    public:
        EnemyAI(GameEngine::GameObject* owner):
            GameEngine::BoxCollider(owner) {
            this->isTrigger = true;
            this->size = { 200.f, 200.f };
        }
        GameEngine::GameObject* target = nullptr;
        float speed = 120.f;

        void OnTriggerEnter(GameEngine::Collider* other) override;
        void OnTriggerStay(GameEngine::Collider* other) override;
        void OnTriggerExit(GameEngine::Collider* other) override;
    };
}
