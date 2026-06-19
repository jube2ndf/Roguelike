#pragma once
#include <GameObject.h>
namespace Roguelike
{
enum class DamageType
{
    Physical,
    Spiritual,
    Elementary,
};
struct Damage
{
    float base = 0.f;

    GameEngine::GameObject* source = nullptr;
    GameEngine::GameObject* target = nullptr;

    float critChance = 0.f;
    float critMultiplier = 1.f;

    struct Context
    {
        DamageType damageType = DamageType::Physical;
    } context;
};
}