#pragma once
#include "Scene.h"
#include "TransformComponent.h"
#include "Component.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionPair.h"
#include "ITriggerListener.h"
#include "CollisionPairHash.h"
#include "CollisionManifold.h"
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <SFML/System/Vector2.hpp>


namespace GameEngine {
    class CollisionSystem
    {
    public:
        void Update(Scene* scene)
        {
            std::vector<Collider*> colliders;

            for (auto& obj : scene->GetObjects())
            {
                auto comps = obj->GetComponents<Collider>();
                for (auto* col : comps)
                    colliders.push_back(col);
            }
            std::unordered_set<CollisionPair, CollisionPairHash> current;
            CollisionManifold manifold;
            for (size_t i = 0; i < colliders.size(); i++)
            {
                for (size_t j = 0; j < colliders.size(); j++)
                {
                    if (i != j && CheckCollision(colliders[i], colliders[j], manifold))
                    {
                        if (colliders[i]->isTrigger || colliders[j]->isTrigger)
                        {
                            CollisionPair pair{ colliders[i], colliders[j] };
                            
                            current.insert(pair);
                        }
                        else
                        {
                            ResolveCollision(colliders[i], colliders[j], manifold);
                        }
                    }
                }
            }

            // Exit / Enter / Stay логика
            ProcessEvents(current);

            _previousCollisions = std::move(current);

            scene->DestroyMarked();
        }

        void RemoveObject(GameObject* obj);

    private:
        std::unordered_set<CollisionPair, CollisionPairHash>
            _previousCollisions;

        inline void ResolveCollision(
            Collider* a,
            Collider* b,
            const CollisionManifold& manifold)
        {
            auto ta =
                a->GetGameObject()->GetComponent<TransformComponent>();

            auto tb =
                b->GetGameObject()->GetComponent<TransformComponent>();

            auto rbA =
                a->GetGameObject()->GetComponent<Rigidbody>();

            auto rbB =
                b->GetGameObject()->GetComponent<Rigidbody>();

            bool moveA =
                rbA && !rbA->isKinematic;

            bool moveB =
                rbB && !rbB->isKinematic;

            if (!moveA && !moveB)
                return;

            sf::Vector2f correction =
                manifold.normal * manifold.penetration;

            if (moveA && moveB)
            {
                ta->MoveBy(-correction * 0.5f);
                tb->MoveBy(correction * 0.5f);
            }
            else if (moveA)
            {
                ta->MoveBy(-correction);
            }
            else if (moveB)
            {
                tb->MoveBy(correction);
            }

            auto RemoveNormalVelocity =
                [](Rigidbody* rb,
                    const sf::Vector2f& normal)
                {
                    if (!rb)
                        return;

                    float dot =
                        rb->velocity.x * normal.x +
                        rb->velocity.y * normal.y;

                    if (dot >= 0.f)
                        return;

                    rb->velocity -= normal * dot;
                };

            RemoveNormalVelocity(rbA, manifold.normal);
            RemoveNormalVelocity(rbB, -manifold.normal);
        }

        void SendTriggerEvent(Collider* a, Collider* b)
        {
            CallListenersEnter(a, b);
        }

        void CallListenersEnter(Collider* self, Collider* other)
        {
            auto listener =
                dynamic_cast<ITriggerListener*>(self);

            if (listener)
            {
                listener->OnTriggerEnter(other);
            }
        }
        void CallListenersStay(Collider* self, Collider* other)
        {
            auto listener =
                dynamic_cast<ITriggerListener*>(self);

            if (listener)
            {
                listener->OnTriggerStay(other);
            }
        }

        void CallListenersExit(Collider* self, Collider* other)
        {
            auto listener =
                dynamic_cast<ITriggerListener*>(self);

            if (listener)
            {
                listener->OnTriggerExit(other);
            }
        }

        void ProcessEvents(
            const std::unordered_set<CollisionPair, CollisionPairHash>& current)
        {
            for (auto& pair : current)
            {
                if (_previousCollisions.find(pair) == _previousCollisions.end())
                {
                    CallListenersEnter(pair.a, pair.b);
                    CallListenersEnter(pair.b, pair.a);
                }
                else
                {
                    CallListenersStay(pair.a, pair.b);
                    CallListenersStay(pair.b, pair.a);
                }
            }

            for (auto& pair : _previousCollisions)
            {
                if (current.find(pair) == current.end())
                {
                    CallListenersExit(pair.a, pair.b);
                    CallListenersExit(pair.b, pair.a);
                }
            }
        }

        bool CheckCollision(
            Collider* a,
            Collider* b,
            CollisionManifold& manifold)
        {
            if (auto boxA = dynamic_cast<BoxCollider*>(a))
            {
                if (auto boxB = dynamic_cast<BoxCollider*>(b))
                    return CheckBoxBox(boxA, boxB, manifold);
            }
            return false;
        }

        inline bool CheckBoxBox(
            BoxCollider* a,
            BoxCollider* b,
            CollisionManifold& manifold)
        {
            manifold = CollisionManifold{};
            auto ta = a->GetGameObject()->GetComponent<TransformComponent>();
            auto tb = b->GetGameObject()->GetComponent<TransformComponent>();

            if (!ta || !tb)
                return false;

            sf::Vector2f posA = ta->GetWorldPosition();
            sf::Vector2f posB = tb->GetWorldPosition();

            sf::Vector2f halfA = a->GetHalfSize();
            sf::Vector2f halfB = b->GetHalfSize();

            sf::Vector2f delta =
            {
                posB.x - posA.x,
                posB.y - posA.y
            };

            float overlapX =
                halfA.x + halfB.x - std::abs(delta.x);

            if (overlapX <= 0.f)
                return false;

            float overlapY =
                halfA.y + halfB.y - std::abs(delta.y);

            if (overlapY <= 0.f)
                return false;

            manifold.collided = true;

            if (overlapX < overlapY)
            {
                manifold.penetration = overlapX;

                manifold.normal =
                {
                    delta.x > 0.f ? 1.f : -1.f,
                    0.f
                };
            }
            else
            {
                manifold.penetration = overlapY;

                manifold.normal =
                {
                    0.f,
                    delta.y > 0.f ? 1.f : -1.f
                };
            }

            return true;
        }
        
    };
}