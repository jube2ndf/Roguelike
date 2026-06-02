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
                auto rb =
                    obj->GetComponent<Rigidbody>();

                auto tr =
                    obj->GetComponent<TransformComponent>();

                if (!rb || !tr)
                    continue;

                if (rb->isKinematic)
                    continue;

                tr->MoveBy(
                    rb->velocity * dt
                );
            }
        }
    };
}