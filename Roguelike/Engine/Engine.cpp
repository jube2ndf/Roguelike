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
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>

Engine::Engine()
{
	
}

void Engine::Initialize()
{
	std::cout << "Engine initialized\n";
}

void Engine::Run(GameEngine::SceneManager& scenes)
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Engine");

    GameEngine::RenderSystem render;
    GameEngine::PhysicsSystem physics;
    GameEngine::CollisionSystem collision;
    GameEngine::UpdateSystem update;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional<sf::Event> e = window.pollEvent())
        {
            if (e->is<sf::Event::Closed>())
                window.close();
        }

        GameEngine::Scene* scene = scenes.GetActiveScene();

        if (!scene)
            continue;

        update.Update(scene, dt);
        physics.Update(scene, dt);
        collision.Update(scene);

        window.clear();
        render.Render(window, scene);
        window.display();
    }
}
