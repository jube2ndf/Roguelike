#pragma once
#include "Scene.h"
namespace GameEngine {
    class UpdateSystem
    {
    public:
        void Update(Scene* scene, float dt)
        {
            for (auto& obj : scene->GetObjects())
            {
                for (auto& comp : obj->GetComponents<Component>())
                {
                    if (comp->IsActive())
                        comp->Update(dt);
                }
            }
        }
    };
}