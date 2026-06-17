#pragma once
#include <GameObject.h>
namespace Roguelike
{
struct BossDiedEvent
{
    GameEngine::GameObject* boss;
};
} // namespace Roguelike