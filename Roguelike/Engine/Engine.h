#pragma once

#include "EngineAPI.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "IGameLayer.h"

class ENGINE_API Engine {
public:
	Engine();
	void Initialize();
	void Run();

	GameEngine::SceneManager& GetSceneManager();
	void AddLayer(GameEngine::IGameLayer* layer);

private:
	sf::RenderWindow _window;
	GameEngine::SceneManager _sceneManager;
	std::vector<GameEngine::IGameLayer*> _layers;
};
