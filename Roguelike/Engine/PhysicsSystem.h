#pragma once
#include "Scene.h"
#include "Rigidbody.h"

namespace GameEngine {
    class PhysicsSystem
    {
    public:
        void Update(Scene* scene, float dt)
        {
            for (auto& obj : scene->GetObjects())
            {
                auto transform = obj->GetComponent<TransformComponent>();
                auto rb = obj->GetComponent<Rigidbody>();

                if (!transform || !rb || rb->isKinematic)
                    continue;

                transform->MoveBy(rb->velocity * dt);

                float damp = 1.f - rb->drag * dt;
                if (damp < 0.f)
                    damp = 0.f;

                rb->velocity *= damp;
            }
        }
    };
}