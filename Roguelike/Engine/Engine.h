#pragma once
#include "EngineAPI.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "IGameLayer.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "UpdateSystem.h"
#include "CollisionSystem.h"

class ENGINE_API Engine {
public:
	Engine();
	void Initialize();
	void Run();

	GameEngine::SceneManager& GetSceneManager();
	void AddLayer(GameEngine::IGameLayer* layer);
    void ClearCollision();

  private:
    GameEngine::RenderSystem render;
    GameEngine::PhysicsSystem physics;
    GameEngine::CollisionSystem collision;
    GameEngine::UpdateSystem update;

	sf::RenderWindow _window;
	GameEngine::SceneManager _sceneManager;
	std::vector<GameEngine::IGameLayer*> _layers;
};
