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

namespace Roguelike
{
class Dragon
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

        rb->mass = 30.f;

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

        enemy->AddComponent<StatsComponent>(
            std::unordered_map<StatType, float>{
                {StatType::MaxHealth, 20.f},
                {StatType::MoveSpeed, 70.f},
                {StatType::Armor, 50.f}});

        auto enemyAI =
            enemy->AddComponent<EntityVision>();
        enemyAI->layer = CollisionLayers::Vision;
        enemyAI->mask =
            CollisionLayers::PlayerBody;

        auto rend = enemy->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Dragon.png"));
        rend->sortingLayer = 10;
        collider->size = {16, 16};


        enemy->AddComponent<GameEngine::TagComponent>("Boss");

        auto ai = enemy->AddComponent<EnemyAI>();

        SwordProjectile::AddRotatingProjectile(enemy, WeaponType::FireBallRotating);
        SwordProjectile::AddSwordProjectile(enemy, WeaponType::FireBallFast);

        enemy->AddComponent<HealthComponent>();

        auto armor = enemy->AddComponent<ArmorComponent>();

        return enemy;
    }
};
} // namespace Roguelike