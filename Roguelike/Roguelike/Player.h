#pragma once
#include <GameObject.h>
#include <Rigidbody.h>
#include <BoxCollider.h>
#include <Scene.h>
#include <ShapeRenderer.h>
#include "PlayerMovementComponent.h"
#include <SFML/System/Vector2.hpp>
namespace Roguelike {
	class Player
	{
    public:
        static GameEngine::GameObject* Create(GameEngine::Scene& scene, sf::Vector2f pos)
        {
            auto player = scene.CreateObject();

            player->AddComponent<PlayerMovementComponent>();

            auto t = player->GetComponent<GameEngine::TransformComponent>();
            t->SetWorldPosition(pos);

            auto rb =
                player->AddComponent<GameEngine::Rigidbody>();

            rb->drag = 5.f;

            auto collider =
                player->AddComponent<GameEngine::BoxCollider>();

            auto shapeRenderer =
                player->AddComponent<GameEngine::ShapeRenderer>();

            collider->size = { 32,32 };

            return player;
        }
	};
}
