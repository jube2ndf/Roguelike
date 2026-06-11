#pragma once

namespace CollisionLayers
{
    constexpr unsigned __int32 GameObject = 1 << 0;
    constexpr unsigned __int32 PlayerBody = 1 << 1;
    constexpr unsigned __int32 EnemyBody = 1 << 2;
    constexpr unsigned __int32 Vision = 1 << 3;
    constexpr unsigned __int32 Attack = 1 << 4;
}