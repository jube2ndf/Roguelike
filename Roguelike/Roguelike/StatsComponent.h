#pragma once
#include <unordered_map>
#include <Component.h>
#include "StatModifier.h"

namespace Roguelike
{
class StatsComponent : public GameEngine::Component
{
  public:
    StatsComponent(GameEngine::GameObject* owner, std::unordered_map<StatType, float> stats);

    void AddModifier(const StatModifier& modifier);

    void RemoveSource(uint64_t sourceId);

    float GetStat(StatType type);

  private:
    std::unordered_map<StatType, float> baseStats;

    std::vector<StatModifier> modifiers;
};
} // namespace Roguelike
