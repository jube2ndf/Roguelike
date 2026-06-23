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
#include "EntityVision.h"
#include "AttackComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "CollisionLayers.h"
#include "EnemyAI.h"
#include <Logger.h>
#include "SwordProjectile.h"
namespace Roguelike {
    class Enemy
    {
    public:
        static GameEngine::GameObject* Create(GameEngine::Scene& scene, sf::Vector2f pos)
        {
            auto enemy = scene.CreateObject();
            LOG_INFO("Game", "Enemy create: " + std::to_string(reinterpret_cast<uintptr_t>(enemy)));
            auto t = enemy->GetComponent<GameEngine::TransformComponent>();
            t->SetWorldPosition(pos);

            auto rb =
                enemy->AddComponent<GameEngine::Rigidbody>();

            rb->mass = 5.f;

            enemy->AddComponent<StatsComponent>(
                std::unordered_map<StatType, float>{
                    {StatType::MaxHealth, 100.f},
                    {StatType::MoveSpeed, 90.f},
                    {StatType::Armor, 10.f}});

            auto collider =
                enemy->AddComponent<GameEngine::BoxCollider>();
            collider->layer = CollisionLayers::EnemyBody |
                              CollisionLayers::DamageTaken;
            collider->mask =
                CollisionLayers::GameObject |
                CollisionLayers::PlayerBody |
                CollisionLayers::Vision |
                CollisionLayers::Attack |
                CollisionLayers::Projectile;

            auto enemyAI =
                enemy->AddComponent<EntityVision>();
            enemyAI->layer = CollisionLayers::Vision;
            enemyAI->mask =
                CollisionLayers::PlayerBody;

            auto rend = enemy->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Player.png"));
            rend->sortingLayer = 10;
            collider->size = { 8,8 };

            enemy->AddComponent<GameEngine::TagComponent>("Enemy");

            enemy->AddComponent<EnemyAI>();

            SwordProjectile::AddSwordProjectile(enemy, WeaponType::SlowSwordProjectile);
            
            enemy->AddComponent<HealthComponent>();

            auto armor = enemy->AddComponent<ArmorComponent>();

            return enemy;
        }
    };
}
