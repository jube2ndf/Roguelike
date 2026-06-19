#pragma once

namespace CollisionLayers
{
    constexpr unsigned __int32 GameObject   = 1 << 0;
    constexpr unsigned __int32 PlayerBody   = 1 << 1;
    constexpr unsigned __int32 EnemyBody    = 1 << 2;
    constexpr unsigned __int32 Vision       = 1 << 3;
    constexpr unsigned __int32 Attack       = 1 << 4;
    constexpr unsigned __int32 Door         = 1 << 5;
    constexpr unsigned __int32 Projectile   = 1 << 6;
    constexpr unsigned __int32 Destructible = 1 << 7;
    constexpr unsigned __int32 DamageTaken = 1 << 8;
}