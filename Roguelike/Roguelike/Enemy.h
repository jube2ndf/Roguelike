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
#include "AttackComponent.h"
#include "EnemyAttackComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
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

            auto enemyAI =
                enemy->AddComponent<EnemyAI>();

            auto rend = enemy->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/Player.png"));

            collider->size = { 32,32 };

            enemy->AddComponent<GameEngine::TagComponent>("Enemy");

            auto attack =
                enemy->AddComponent<AttackComponent>();

            attack->damage = 1.f;
            attack->cooldown = 10000.f;

            enemy->AddComponent<EnemyAttackComponent>();

            enemy->AddComponent<HealthComponent>(100.f);

            enemy->AddComponent<ArmorComponent>();


            return enemy;
        }
    };
}
