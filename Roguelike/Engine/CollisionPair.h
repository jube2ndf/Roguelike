#pragma once
#include "Collider.h"

namespace GameEngine {
    struct CollisionPair
    {
        Collider* a;
        Collider* b;

        bool operator==(const CollisionPair& other) const
        {
            return
                (a == other.a && b == other.b) ||
            (a == other.b && b == other.a);
        }
    };
}