#pragma once
#include <GameObject.h>
#include <Rigidbody.h>
#include <BoxCollider.h>
#include <Logger.h>
#include <Scene.h>
#include <ShapeRenderer.h>
#include "PlayerMovementComponent.h"
#include <SFML/System/Vector2.hpp>
#include <TextureManager.h>
#include <SpriteRenderer.h>
#include <TagComponent.h>
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "EntityVision.h"
#include "CollisionLayers.h"
#include "SimpleAttack.h"
#include "SwordProjectile.h"
#include "Inventory.h"
#include "InventoryUsedComponent.h"

namespace Roguelike {
	class Player
	{
    public:
        static GameEngine::GameObject* Create(GameEngine::Scene& scene, sf::Vector2f pos)
        {
            auto player = scene.CreateObject();
            LOG_INFO("Game", "Player create: " + std::to_string(reinterpret_cast<uintptr_t>(player)));
            player->persistentObjects = true;

            auto t = player->GetComponent<GameEngine::TransformComponent>();
            t->SetWorldPosition(pos);

            auto rb =
                player->AddComponent<GameEngine::Rigidbody>();

            rb->mass = 5.f;

            auto collider =
                player->AddComponent<GameEngine::BoxCollider>();
            collider->layer = CollisionLayers::PlayerBody |
                              CollisionLayers::DamageTaken;
            collider->mask =
                CollisionLayers::GameObject |
                CollisionLayers::EnemyBody |
                CollisionLayers::Vision |
                CollisionLayers::Attack |
                CollisionLayers::Door |
                CollisionLayers::Projectile |
                CollisionLayers::GameItem;

            auto rend = player->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Player.png"));
            rend->sortingLayer = 10;
            collider->size = { 8,8 };

            player->AddComponent<GameEngine::TagComponent>("Player");

            player->AddComponent<StatsComponent>(
                std::unordered_map<StatType, float>{
                    {StatType::MaxHealth, 100.f},
                    {StatType::MoveSpeed, 120.f},
                    {StatType::Armor, 10.f}});

            player->AddComponent<PlayerMovementComponent>();
            player->AddComponent<HealthComponent>();

            auto armor = player->AddComponent<ArmorComponent>();
            
            player->AddComponent<SimpleAttack>();

            SwordProjectile::AddSwordProjectile(player, WeaponType::FastSwordProjectile);

            player->AddComponent<InventoryComponent>();
            player->AddComponent<InventoryUsedComponent>();

            scene.GetCamera().Follow(player);
            return player;
        }
	};
}
