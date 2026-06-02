#include "pch.h"
#include "Engine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ShapeRenderer.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "PhysicsSystem.h"
#include "UpdateSystem.h"
#include "CollisionSystem.h"
#include "SceneManager.h"
#include "EventBus.h"
#include "ChangeSceneEvent.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

Engine::Engine()
{
	
}

void Engine::Initialize()
{
	std::cout << "Engine initialized\n";
    GameEngine::EventBus::Subscribe<GameEngine::ChangeSceneEvent>(
        [this](const GameEngine::ChangeSceneEvent& e)
        {
            _sceneManager.SwitchScene(e.sceneName);
        });
    _window.create(sf::VideoMode({ 1280, 720 }), "Game");
    std::cout << "Window created\n";
    std::cout << "isOpen: " << _window.isOpen() << std::endl;
}

void Engine::Run()
{
    sf::Clock clock;
    float accumulator = 0.f;

    GameEngine::RenderSystem render;
    GameEngine::PhysicsSystem physics;
    GameEngine::CollisionSystem collision;
    GameEngine::UpdateSystem update;

    while (this->_window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        if (dt > 0.25f)
            dt = 0.25f;

        accumulator += dt;

        while (const std::optional<sf::Event> e = this->_window.pollEvent())
        {
            if (e->is<sf::Event::Closed>())
                this->_window.close();
        }

        GameEngine::Scene* scene = this->_sceneManager.GetActiveScene();

        if (!scene)
            continue;

        update.Update(scene, dt);


        while (accumulator >= FIXED_TIMESTEP)
        {
            physics.Update(scene, FIXED_TIMESTEP);
            collision.Update(scene);

            accumulator -= FIXED_TIMESTEP;
        }

        render.Render(this->_window, scene);
    }
}

GameEngine::SceneManager& Engine::GetSceneManager()
{
    return this->_sceneManager;
}
