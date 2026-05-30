#pragma once
#include "CollisionPair.h"

namespace GameEngine {
    struct CollisionPairHash
    {
        size_t operator()(const CollisionPair& pair) const
        {
            auto ptrA =
                reinterpret_cast<size_t>(pair.a);

            auto ptrB =
                reinterpret_cast<size_t>(pair.b);

            if (ptrA > ptrB)
                std::swap(ptrA, ptrB);

            return ptrA ^ (ptrB << 1);
        }
    };
}