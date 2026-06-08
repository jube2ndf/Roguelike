#pragma once
#include <GameObject.h>
#include <Rigidbody.h>
#include <BoxCollider.h>
#include <Scene.h>
#include <ShapeRenderer.h>
#include "PlayerMovementComponent.h"
#include <SFML/System/Vector2.hpp>
#include <TextureManager.h>
#include <SpriteRenderer.h>
#include <TagComponent.h>
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "PlayerAttackComponent.h"
#include "AttackTriggerComponent.h"

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

            rb->mass = 5.f;

            auto collider =
                player->AddComponent<GameEngine::BoxCollider>();

            auto rend = player->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Player.png"));

            collider->size = { 32,32 };

            player->AddComponent<GameEngine::TagComponent>("Player");

            player->AddComponent<HealthComponent>(100.f);

            player->AddComponent<ArmorComponent>();

            auto AttackComponent = player->AddComponent<PlayerAttackComponent>();

            AttackComponent->damage = 30.f;
            AttackComponent->cooldown = 5.f;
            AttackComponent->distance = 50.f;

            auto AttackTrigger = player->AddComponent<AttackTriggerComponent>();

            return player;
        }
	};
}
