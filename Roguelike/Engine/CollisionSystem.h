#pragma once
#include "Scene.h"
#include "TransformComponent.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionPair.h"
#include "ITriggerListener.h"
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
            std::unordered_set<CollisionPair> current;

            for (size_t i = 0; i < colliders.size(); i++)
            {
                for (size_t j = i + 1; j < colliders.size(); j++)
                {
                    if (CheckCollision(colliders[i], colliders[j]))
                    {
                        CollisionPair pair{ colliders[i], colliders[j] };

                        current.insert(pair);

                        HandleTrigger(colliders[i], colliders[j]);
                    }
                }
            }

            // Exit / Enter / Stay логика
            ProcessEvents(current);

            _previousCollisions = std::move(current);

            scene->DestroyMarked();
        }
    private:
        std::unordered_set<CollisionPair>
            _previousCollisions;

        void HandleTrigger(Collider* a, Collider* b)
        {
            if (a->isTrigger || b->isTrigger)
            {
                SendTriggerEvent(a, b);
            }
            else
            {
                ResolveCollision(a, b);
            }
        }

        void ResolveCollision(Collider* a, Collider* b) {

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
            const std::unordered_set<CollisionPair>& current)
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
            Collider* b)
        {
            if (auto boxA =
                dynamic_cast<BoxCollider*>(a))
            {
                if (auto boxB =
                    dynamic_cast<BoxCollider*>(b))
                {
                    return CheckBoxBox(boxA, boxB);
                }

                if (auto circleB =
                    dynamic_cast<CircleCollider*>(b))
                {
                    return CheckBoxCircle(
                        boxA,
                        circleB);
                }
            }

            if (auto circleA =
                dynamic_cast<CircleCollider*>(a))
            {
                if (auto circleB =
                    dynamic_cast<CircleCollider*>(b))
                {
                    return CheckCircleCircle(
                        circleA,
                        circleB);
                }

                if (auto boxB =
                    dynamic_cast<BoxCollider*>(b))
                {
                    return CheckBoxCircle(
                        boxB,
                        circleA);
                }
            }

            return false;
        }

        bool CheckBoxBox(
            BoxCollider* a,
            BoxCollider* b)
        {
            auto posA =
                a->GetWorldPosition();

            auto posB =
                b->GetWorldPosition();

            return
                posA.x < posB.x + b->size.x &&
                posA.x + a->size.x > posB.x &&
                posA.y < posB.y + b->size.y &&
                posA.y + a->size.y > posB.y;
        }

        bool CheckCircleCircle(
            CircleCollider* a,
            CircleCollider* b)
        {
            auto posA =
                a->GetWorldPosition();

            auto posB =
                b->GetWorldPosition();

            float dx = posA.x - posB.x;
            float dy = posA.y - posB.y;

            float distanceSquared =
                dx * dx + dy * dy;

            float radiusSum =
                a->radius + b->radius;

            return distanceSquared <
                radiusSum * radiusSum;
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
            CircleCollider* circle
        ) {
            auto boxPos =
                box->GetWorldPosition();

            auto circlePos =
                circle->GetWorldPosition();

            float closestX =
                Clamp(circlePos.x,
                    boxPos.x,
                    boxPos.x + box->size.x);

            float closestY =
                Clamp(circlePos.y,
                    boxPos.y,
                    boxPos.y + box->size.y);

            float dx =
                circlePos.x - closestX;

            float dy =
                circlePos.y - closestY;

            return dx * dx + dy * dy <
                circle->radius * circle->radius;
        }
    };
}