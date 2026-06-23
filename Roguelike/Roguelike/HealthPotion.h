#pragma once
#include "IItem.h"
namespace Roguelike
{
class HealthPotion : public IItem
{
  public:
    HealthPotion(float healAmount)
        : healAmount(healAmount) {};

    void Use(GameEngine::GameObject* user) override;
    std::string GetName() const;

  private: 
    std::string name = "Health potion";
    float healAmount = 50.f;
};
} // namespace Roguelike
