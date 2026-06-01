#pragma once
#include "Scene.h"
#include "TransformComponent.h"
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
                auto col = obj->GetComponent<Collider>();
                if (col) colliders.push_back(col);
            }
            std::unordered_set<CollisionPair, CollisionPairHash> current;
            CollisionManifold manifold;
            for (size_t i = 0; i < colliders.size(); i++)
            {
                for (size_t j = i + 1; j < colliders.size(); j++)
                {
                    if (CheckCollision(colliders[i], colliders[j], manifold))
                    {
                        CollisionPair pair{ colliders[i], colliders[j] };

                        current.insert(pair);

                        HandleTrigger(colliders[i], colliders[j], manifold);
                    }
                }
            }

            // Exit / Enter / Stay логика
            ProcessEvents(current);

            _previousCollisions = std::move(current);

            scene->DestroyMarked();
        }
    private:
        std::unordered_set<CollisionPair, CollisionPairHash>
            _previousCollisions;

        void HandleTrigger(Collider* a, Collider* b, CollisionManifold& manifold)
        {
            if (a->isTrigger || b->isTrigger)
            {
                SendTriggerEvent(a, b);
            }
            else
            {
                ResolveCollision(a, b, manifold);
            }
        }

        void ResolveCollision(
            Collider* a,
            Collider* b,
            const CollisionManifold& manifold)
        {
            auto rbA = a->GetGameObject()->GetComponent<Rigidbody>();
            auto rbB = b->GetGameObject()->GetComponent<Rigidbody>();

            auto ta = a->GetGameObject()->GetComponent<TransformComponent>();
            auto tb = b->GetGameObject()->GetComponent<TransformComponent>();

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
        }

        void SendTriggerEvent(Collider* a, Collider* b)
        {
            CallListenersEnter(a, b);
            CallListenersEnter(b, a);
        }

        void CallListenersEnter(Collider* self, Collider* other)
        {
            auto obj = self->GetGameObject();

            for (auto& comp : obj->GetComponents<Component>())
            {
                auto listener =
                    dynamic_cast<ITriggerListener*>(comp);

                if (listener)
                    listener->OnTriggerEnter(other);
            }
        }
        void CallListenersStay(Collider* self, Collider* other)
        {
            auto obj = self->GetGameObject();

            for (auto& comp : obj->GetComponents<Component>())
            {
                auto listener =
                    dynamic_cast<ITriggerListener*>(comp);

                if (listener)
                    listener->OnTriggerStay(other);
            }
        }

        void CallListenersExit(Collider* self, Collider* other)
        {
            auto obj = self->GetGameObject();

            for (auto& comp : obj->GetComponents<Component>())
            {
                auto listener =
                    dynamic_cast<ITriggerListener*>(comp);

                if (listener)
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
                }
                else
                {
                    CallListenersStay(pair.a, pair.b);
                }
            }

            for (auto& pair : _previousCollisions)
            {
                if (current.find(pair) == current.end())
                {
                    CallListenersExit(pair.a, pair.b);
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

                if (auto circleB = dynamic_cast<CircleCollider*>(b))
                    return CheckBoxCircle(boxA, circleB, manifold);
            }

            if (auto circleA = dynamic_cast<CircleCollider*>(a))
            {
                if (auto circleB = dynamic_cast<CircleCollider*>(b))
                    return CheckCircleCircle(circleA, circleB, manifold);

                if (auto boxB = dynamic_cast<BoxCollider*>(b))
                {
                    bool result =
                        CheckBoxCircle(boxB, circleA, manifold);

                    manifold.normal *= -1.f;

                    return result;
                }
            }

            return false;
        }

        bool CheckBoxBox(
            BoxCollider* a,
            BoxCollider* b,
            CollisionManifold& manifold)
        {
            auto posA = a->GetWorldPosition();
            auto posB = b->GetWorldPosition();

            float overlapX =
                std::min<float>(posA.x + a->size.x,
                    posB.x + b->size.x)
                -
                std::max<float>(posA.x, posB.x);

            if (overlapX <= 0.f)
                return false;

            float overlapY =
                std::min<float>(posA.y + a->size.y,
                    posB.y + b->size.y)
                -
                std::max<float>(posA.y, posB.y);

            if (overlapY <= 0.f)
                return false;

            sf::Vector2f centerA =
            {
                posA.x + a->size.x * 0.5f,
                posA.y + a->size.y * 0.5f
            };

            sf::Vector2f centerB =
            {
                posB.x + b->size.x * 0.5f,
                posB.y + b->size.y * 0.5f
            };

            if (overlapX < overlapY)
            {
                manifold.penetration = overlapX;

                manifold.normal =
                {
                    centerA.x < centerB.x ? -1.f : 1.f,
                    0.f
                };
            }
            else
            {
                manifold.penetration = overlapY;

                manifold.normal =
                {
                    0.f,
                    centerA.y < centerB.y ? -1.f : 1.f
                };
            }

            return true;
        }

        bool CheckCircleCircle(
            CircleCollider* a,
            CircleCollider* b,
            CollisionManifold& manifold)
        {
            auto posA = a->GetWorldPosition();
            auto posB = b->GetWorldPosition();

            sf::Vector2f delta =
            {
                posB.x - posA.x,
                posB.y - posA.y
            };

            float distanceSquared =
                delta.x * delta.x +
                delta.y * delta.y;

            float radiusSum =
                a->radius + b->radius;

            if (distanceSquared >= radiusSum * radiusSum)
                return false;

            float distance = std::sqrt(distanceSquared);

            if (distance < 0.0001f)
            {
                manifold.normal = { 1.f, 0.f };
                manifold.penetration = radiusSum;
                return true;
            }

            manifold.normal =
            {
                delta.x / distance,
                delta.y / distance
            };

            manifold.penetration =
                radiusSum - distance;

            return true;
        }

        float Clamp(float value,
            float minValue,
            float maxValue)
        {
            return std::max<float>(minValue,
                std::min<float>(value, maxValue));
        }

        bool CheckBoxCircle(
            BoxCollider* box,
            CircleCollider* circle,
            CollisionManifold& manifold)
        {
            auto boxPos =
                box->GetWorldPosition();

            auto circlePos =
                circle->GetWorldPosition();

            float closestX =
                Clamp(
                    circlePos.x,
                    boxPos.x,
                    boxPos.x + box->size.x);

            float closestY =
                Clamp(
                    circlePos.y,
                    boxPos.y,
                    boxPos.y + box->size.y);

            float dx =
                circlePos.x - closestX;

            float dy =
                circlePos.y - closestY;

            float distanceSquared =
                dx * dx + dy * dy;

            float radiusSquared =
                circle->radius * circle->radius;

            if (distanceSquared >= radiusSquared)
                return false;

            float distance =
                std::sqrt(distanceSquared);

            if (distance < 0.0001f)
            {
                manifold.normal = { 1.f, 0.f };
                manifold.penetration = circle->radius;
                return true;
            }

            manifold.normal =
            {
                dx / distance,
                dy / distance
            };

            manifold.penetration =
                circle->radius - distance;

            return true;
        }
    };
}