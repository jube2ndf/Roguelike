#pragma once
#include <GameObject.h>
#include <Rigidbody.h>
#include <BoxCollider.h>
#include <Scene.h>
#include "PlayerMovementComponent.h"
namespace Roguelike {
	class Player
	{
    public:
        static GameEngine::GameObject* Create(GameEngine::Scene& scene)
        {
            auto player = scene.CreateObject();

            player->AddComponent<PlayerMovementComponent>();

            auto rb =
                player->AddComponent<GameEngine::Rigidbody>();

            rb->drag = 5.f;

            auto collider =
                player->AddComponent<GameEngine::BoxCollider>();

            collider->size = { 32,32 };

            return player;
        }
	};
}
