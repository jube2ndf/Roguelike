#pragma once
#include <Component.h>
namespace Roguelike {
    class PlayerMovementComponent :
        public GameEngine::Component
    {
    public:
        void Update(float dt) override;

        float speed = 200.f;
    };
}
