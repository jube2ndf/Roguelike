#pragma once
#include <cstdint>
#include "StatType.h"
#include "StatSource.h"

namespace Roguelike
{
struct StatModifier
{
    StatType stat;

    float flatValue = 0.f;
    float percentValue = 0.f;

    StatSource source;
    uint64_t sourceId = 0;
};
}