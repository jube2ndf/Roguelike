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
                for (auto& obj : scene->GetObjects())
                {
                    auto rb = obj->GetComponent<Rigidbody>();
                    auto transform = obj->GetComponent<TransformComponent>();

                    if (!rb || !transform)
                        continue;

                    if (rb->isKinematic)
                        continue;

                    // 1. ускорение → скорость
                    rb->velocity += rb->acceleration * dt;

                    // 2. drag (плавное затухание)
                    rb->velocity *= std::max<float>(0.f, 1.f - rb->drag * dt);

                    // 3. перемещение
                    transform->MoveBy(rb->velocity * dt);
                }
            }
        }
    };
}