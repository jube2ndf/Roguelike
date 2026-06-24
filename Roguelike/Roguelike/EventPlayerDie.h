#pragma once
#include <GameObject.h>
namespace Roguelike
{
struct EventPlayerDied
{
    GameEngine::GameObject* boss;
};
} // namespace Roguelike