#pragma once
#include "EngineAPI.h"
#include <SFML/Graphics/View.hpp>
#include "GameObject.h"
namespace GameEngine {
class ENGINE_API Camera {
public:
  Camera();

  void SetPosition(sf::Vector2f position);
  void Move(sf::Vector2f delta);

  void SetSize(sf::Vector2f size);

  sf::View &GetView();

  void Follow(GameEngine::GameObject *target);

  void Update();

private:
  GameEngine::GameObject *_target;
  sf::View _view;
};
} // namespace GameEngine
