#pragma once
#include <SFML/Graphics.hpp>
#include "SceneCommand.h"

namespace Interface {
	class IScene {
	public:
		virtual ~IScene() = default;
		virtual Scene::SceneCommand handleInput(sf::Event& event) = 0;
		virtual Scene::SceneCommand update(float dt) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;

		virtual void pause() {}
		virtual void resume() {}
	};
}