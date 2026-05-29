#include "pch.h"
#include "Engine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ShapeRenderer.h"
#include "RenderSystem.h"
#include "Scene.h"
#include <iostream>
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
	std::cout << "Engine run\n";
    sf::RenderWindow window(
        sf::VideoMode({ 1280, 720 }),
        "Engine");

    GameEngine::Scene scene;

    GameEngine::RenderSystem renderSystem;

    auto obj = scene.CreateObject();

    auto transform = obj->GetComponent<GameEngine::TransformComponent>();

    transform->MoveBy({});

    obj->AddComponent<GameEngine::ShapeRenderer>();

    while (window.isOpen())
    {
        while (const auto event =
            window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        renderSystem.Render(window, &scene);

        window.display();
    }
}
