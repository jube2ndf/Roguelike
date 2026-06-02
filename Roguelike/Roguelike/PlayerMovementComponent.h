#pragma once
#include <Component.h>
#include <GameObject.h>
namespace Roguelike {
    class PlayerMovementComponent :
        public GameEngine::Component
    {
    public:
        PlayerMovementComponent(GameEngine::GameObject* owner):
            GameEngine::Component(owner){}
        void Update(float dt) override;

        float speed = 200.f;
    };
}
