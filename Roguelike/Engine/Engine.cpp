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

void Engine::Run()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Engine");

    GameEngine::Scene scene;
    auto obj = scene.CreateObject();

    auto transform = obj->GetComponent<GameEngine::TransformComponent>();

    transform->MoveBy({ 1280/2, 720/2 });

    obj->AddComponent<GameEngine::ShapeRenderer>();


    GameEngine::RenderSystem renderSystem;
    GameEngine::PhysicsSystem physicsSystem;
    GameEngine::CollisionSystem collisionSystem;
    GameEngine::UpdateSystem updateSystem;

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // 1. UPDATE (логика компонентов)
        updateSystem.Update(&scene, dt);

        // 2. PHYSICS (движение)
        physicsSystem.Update(&scene, dt);

        // 3. COLLISIONS
        collisionSystem.Update(&scene);

        // 4. RENDER
        window.clear();
        renderSystem.Render(window, &scene);
        window.display();
    }
}
