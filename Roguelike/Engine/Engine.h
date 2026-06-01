#pragma once

#include "EngineAPI.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

class ENGINE_API Engine {
public:
	Engine();
	void Initialize();
	void Run();

	GameEngine::SceneManager& GetSceneManager();

private:
	sf::RenderWindow _window;
	GameEngine::SceneManager _sceneManager;
};
