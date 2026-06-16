#include "Camera.h"
#include "pch.h"

void GameEngine::Camera::SetPosition(sf::Vector2f position) {
  this->_view.setCenter(position);
}

void GameEngine::Camera::Move(sf::Vector2f delta) { this->_view.move(delta); }

void GameEngine::Camera::SetSize(sf::Vector2f size) {
  this->_view.setSize(size);
}

sf::View &GameEngine::Camera::GetView() { return this->_view; }
