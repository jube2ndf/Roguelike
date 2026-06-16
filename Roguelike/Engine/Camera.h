#pragma once
#include "EngineAPI.h"

namespace GameEngine {
class ENGINE_API Camera {
public:
  void SetPosition(sf::Vector2f position);
  void Move(sf::Vector2f delta);

  void SetSize(sf::Vector2f size);

  sf::View &GetView();

private:
  sf::View _view;
};
} // namespace GameEngine
