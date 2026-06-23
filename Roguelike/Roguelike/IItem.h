#pragma once
#include <GameObject.h>
namespace Roguelike
{
class IItem
{
  public:
    virtual ~IItem() {};

    virtual void Use(GameEngine::GameObject* user) = 0;
    virtual std::string GetName() const = 0;
};
}