#include "pch.h"
#include "CollisionSystem.h"

void GameEngine::CollisionSystem::RemoveObject(GameObject* obj)
{
    std::erase_if(
        _previousCollisions,
        [&](const CollisionPair& pair)
        {
            bool contains =
                pair.a->GetGameObject() == obj ||
                pair.b->GetGameObject() == obj;

            if (contains)
            {
                CallListenersExit(pair.a, pair.b);
                CallListenersExit(pair.b, pair.a);
            }

            return contains;
        });
}
