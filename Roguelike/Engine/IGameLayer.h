#pragma once
#include "EngineAPI.h"
namespace GameEngine {
    class ENGINE_API IGameLayer
    {
    public:
        virtual ~IGameLayer() = default;

        virtual void Update(float dt) = 0;
    };
}