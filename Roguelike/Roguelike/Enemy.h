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
namespace Roguelike {
    class Enemy
    {
    public:
        static GameEngine::GameObject* Create(GameEngine::Scene& scene, sf::Vector2f pos)
        {
            auto enemy = scene.CreateObject();

            auto t = enemy->GetComponent<GameEngine::TransformComponent>();
            t->SetWorldPosition(pos);

            auto rb =
                enemy->AddComponent<GameEngine::Rigidbody>();

            rb->mass = 5.f;

            auto collider =
                enemy->AddComponent<GameEngine::BoxCollider>();
            collider->layer = CollisionLayers::EnemyBody;
            collider->mask =
                CollisionLayers::GameObject |
                CollisionLayers::PlayerBody |
                CollisionLayers::Vision |
                CollisionLayers::Attack;

            auto enemyAI =
                enemy->AddComponent<EntityVision>();
            enemyAI->layer = CollisionLayers::Vision;
            enemyAI->mask =
                CollisionLayers::PlayerBody;

            auto rend = enemy->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Player.png"));

            collider->size = { 32,32 };

            enemy->AddComponent<GameEngine::TagComponent>("Enemy");

            auto attack =
                enemy->AddComponent<AttackComponent>();

            attack->damage = 25.f;
            attack->cooldown = 10.f;
            attack->timer = 10.f;

            enemy->AddComponent<EnemyAI>();

            enemy->AddComponent<HealthComponent>(100.f);

            auto armor = enemy->AddComponent<ArmorComponent>();
            armor->baseArmor = 10;

            return enemy;
        }
    };
}
