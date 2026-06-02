#pragma once
#include <SFML/System/Vector2.hpp>
#include <GameObject.h>
#include <Rigidbody.h>
#include <BoxCollider.h>
#include <Scene.h>
#include <SpriteRenderer.h>
#include <TextureManager.h>
#include <TransformComponent.h>
namespace Roguelike {
	class Wall
	{
	public:
        static GameEngine::GameObject* CreateWall(GameEngine::Scene& scene, sf::Vector2f pos, sf::Vector2f size)
        {
            auto wall = scene.CreateObject();

            auto t = wall->GetComponent<GameEngine::TransformComponent>();
            t->SetWorldPosition(pos);

            auto col = wall->AddComponent<GameEngine::BoxCollider>();
            col->size = size;

            auto rb = wall->AddComponent<GameEngine::Rigidbody>();
            rb->isKinematic = true;

            auto rend = wall->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("../Resources/Textures/Wall.png"));

            return wall;
        }
	};
}
