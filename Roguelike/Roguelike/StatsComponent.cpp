#include "StatsComponent.h"
#include <algorithm>

Roguelike::StatsComponent::StatsComponent(GameEngine::GameObject* owner, std::unordered_map<StatType, float> stats)
    : Component(owner),
      baseStats(std::move(stats))
{
}

void Roguelike::StatsComponent::AddModifier(const StatModifier& modifier)
{
    modifiers.push_back(modifier);
}

void Roguelike::StatsComponent::RemoveSource(uint64_t sourceId)
{
    modifiers.erase(
        std::remove_if(
            modifiers.begin(),
            modifiers.end(),
            [sourceId](const StatModifier& a) {
                return a.sourceId == sourceId;
            }),
        modifiers.end());
}

float Roguelike::StatsComponent::GetStat(StatType type)
{
    float base = baseStats.at(type);

    float flat = 0.f;
    float percent = 0.f;

    for (const auto& mod : modifiers)
    {
        if (mod.stat != type)
            continue;

        flat += mod.flatValue;
        percent += mod.percentValue;
    }

    return (base + flat) * (1.f + percent);
}
