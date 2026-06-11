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
#include "EntityVision.h"
#include "CollisionLayers.h"

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
            collider->layer = CollisionLayers::PlayerBody;
            collider->mask =
                CollisionLayers::EnemyBody |
                CollisionLayers::Vision |
                CollisionLayers::Attack;
            auto rend = player->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Player.png"));

            collider->size = { 32,32 };

            player->AddComponent<GameEngine::TagComponent>("Player");

            player->AddComponent<HealthComponent>(100.f);

            auto armor = player->AddComponent<ArmorComponent>();
            armor->baseArmor = 10;

            auto AttackComponent = player->AddComponent<PlayerAttackComponent>();

            AttackComponent->damage = 30.f;
            AttackComponent->cooldown = 3.f;
            AttackComponent->timer = 3.f;


            auto entityVision = player->AddComponent<EntityVision>();
            entityVision->layer = CollisionLayers::Vision;
            entityVision->mask = 
                CollisionLayers::EnemyBody;

            return player;
        }
	};
}
