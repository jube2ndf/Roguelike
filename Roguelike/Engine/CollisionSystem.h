#pragma once
#include "Scene.h"
#include "TransformComponent.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include <SFML/System/Vector2.hpp>

namespace GameEngine {
    class CollisionSystem
    {
    private:
        inline bool CheckAABB(
            const sf::Vector2f& posA,
            const sf::Vector2f& sizeA,
            const sf::Vector2f& posB,
            const sf::Vector2f& sizeB)
        {
            return
                std::abs(posA.x - posB.x) < (sizeA.x + sizeB.x) * 0.5f &&
                std::abs(posA.y - posB.y) < (sizeA.y + sizeB.y) * 0.5f;
        }
        inline void ResolveCollision(
            TransformComponent* a,
            Rigidbody* ra,
            TransformComponent* b,
            Rigidbody* rb)
        {
            sf::Vector2f delta = a->GetWorldPosition() - b->GetWorldPosition();

            float dx = std::abs(delta.x);
            float dy = std::abs(delta.y);

            if (dx > dy)
            {
                // по X
                if (delta.x > 0)
                    a->MoveBy({ 1.f,0 });
                else
                    a->MoveBy({ 1.f,0 });

                if (ra)
                    ra->velocity.x = 0.f;
            }
            else
            {
                // по Y
                if (delta.y > 0)
                    a->MoveBy({ 0, 1.f });
                else
                    a->MoveBy({ 0, -1.f });

                if (ra)
                    ra->velocity.y = 0.f;
            }
        }
    public:
        void Update(Scene* scene)
        {
            auto& objects = scene->GetObjects();

            for (size_t i = 0; i < objects.size(); i++)
            {
                for (size_t j = i + 1; j < objects.size(); j++)
                {
                    auto a = objects[i].get();
                    auto b = objects[j].get();

                    auto ta = a->GetComponent<TransformComponent>();
                    auto tb = b->GetComponent<TransformComponent>();

                    auto ca = a->GetComponent<BoxCollider>();
                    auto cb = b->GetComponent<BoxCollider>();

                    auto ra = a->GetComponent<Rigidbody>();
                    auto rb = b->GetComponent<Rigidbody>();

                    if (!ta || !tb || !ca || !cb || !ra || !rb)
                        continue;

                    if (CheckAABB(ta->GetWorldPosition(), ca->size, tb->GetWorldPosition(), cb->size))
                    {
                        ResolveCollision(ta, ra, tb, rb);
                    }
                }
            }
        }
    };
}