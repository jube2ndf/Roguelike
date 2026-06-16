#include "pch.h"
#include "Camera.h"
#include "TransformComponent.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

GameEngine::Camera::Camera() {
  //_view.setSize({1280.f, 720.f});
  _view.setSize({320, 160.f});
  _view.setCenter({640.f, 360.f});
  _target = nullptr;
}

void GameEngine::Camera::SetPosition(sf::Vector2f position) {
  this->_view.setCenter(position);
}

void GameEngine::Camera::Move(sf::Vector2f delta) { this->_view.move(delta); }

void GameEngine::Camera::SetSize(sf::Vector2f size) {
  this->_view.setSize(size);
}

sf::View& GameEngine::Camera::GetView() { return this->_view; }

void GameEngine::Camera::Follow(GameEngine::GameObject *target) {
  this->_target = target;
}

void GameEngine::Camera::Update() {
  if (!this->_target)
    return;

  auto tr = this->_target->GetComponent<GameEngine::TransformComponent>();

  if (tr == nullptr)
    return;
  _view.setCenter(tr->GetWorldPosition());
  SetPosition(tr->GetWorldPosition());
}
