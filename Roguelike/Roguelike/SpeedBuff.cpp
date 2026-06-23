#include "SpeedBuff.h"
#include "StatsComponent.h"

void Roguelike::SpeedBuff::OnApply(GameEngine::GameObject* target)
{
    auto stats =
        target->GetComponent<StatsComponent>();

    stats->AddModifier({StatType::MoveSpeed,
                        this->flatValue,
                        this->percentValue,
                        StatSource::Buff,
                        this->sourceId});
}

void Roguelike::SpeedBuff::OnUpdate(GameEngine::GameObject* target, float dt)
{
    timer -= dt;
}

void Roguelike::SpeedBuff::OnRemove(GameEngine::GameObject* target)
{
    auto stats =
        target->GetComponent<StatsComponent>();

    stats->RemoveSource(sourceId);
}

bool Roguelike::SpeedBuff::IsFinished() const
{
    return this->timer <= 0;
}
