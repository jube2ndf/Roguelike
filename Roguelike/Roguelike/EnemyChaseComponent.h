#pragma once
#include <Component.h>
#include <GameObject.h>
namespace Roguelike {
    class EnemyChaseComponent :
        public GameEngine::Component
    {
    public:
        EnemyChaseComponent(GameEngine::GameObject* owner)
            :GameEngine::Component(owner) {

        }
        void Update(float deltaTime) override;
        float speed = 120.f;
    };
}
