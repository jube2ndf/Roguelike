#pragma once
#include "IEffect.h"
namespace Roguelike
{
class SpeedBuff : public IEffect
{
  public:
    SpeedBuff(float value, float percentValue, float duration)
        : flatValue(value), percentValue(percentValue), timer(duration)
    {
        sourceId = reinterpret_cast<uint64_t>(this);
    }

    // Унаследовано через IEffect
    void OnApply(GameEngine::GameObject* target) override;
    void OnUpdate(GameEngine::GameObject* target, float dt) override;
    void OnRemove(GameEngine::GameObject* target) override;
    bool IsFinished() const override;

    private:
    float flatValue = 0.f;
    float percentValue = 0.f;
    float timer;
    uint64_t sourceId;
};
} // namespace Roguelike
