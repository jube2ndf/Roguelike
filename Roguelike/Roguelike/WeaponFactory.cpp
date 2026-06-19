#include "WeaponFactory.h"
#include <TagComponent.h>
#include "ProjectileComponent.h"
#include <Rigidbody.h>
#include "AttackComponent.h"
#include <TextureManager.h>
#include <SpriteRenderer.h>
#include "BoxCollisionDetector.h"
#include "CollisionLayers.h"
#include "WeaponType.h"

std::unordered_map<Roguelike::WeaponType, float>
    Roguelike::WeaponFactory::culDown = {
    {Roguelike::WeaponType::SlowSword,
     10},
    {Roguelike::WeaponType::FastSword,
     3},
};

void Roguelike::WeaponFactory::Create(GameEngine::Scene& scene, CreateWeapon data)
{
    switch (data.type)
    {
    case Roguelike::WeaponType::SlowSword:
        WeaponFactory::SlowSword(scene, data);
        break;
    case Roguelike::WeaponType::FastSword:
        WeaponFactory::FastSword(scene, data);
        break;
    default:
        break;
    }
}

void Roguelike::WeaponFactory::CreaetSword(GameEngine::Scene& scene, 
    CreateWeapon dto, 
    float damage,
    float critChance,
    float critMultiplier,
    DamageType type,
    float speed,
    WeaponType Wtype
)
{
    GameEngine::GameObject* sword =
        scene.CreateObject();
    sword->AddComponent<GameEngine::TagComponent>("DamageSword");
    auto projectileComponent = sword->AddComponent<ProjectileComponent>(
        damage,
        critChance,
        critMultiplier,
        type,
        dto.source
    );

    auto rend = sword->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load("./Resources/Textures/sword.png"));
    rend->sortingLayer = 10;
    

    auto t = sword->GetComponent<GameEngine::TransformComponent>();
    t->SetWorldPosition(dto.data.position);
    float angle = std::atan2(dto.data.direction.y, dto.data.direction.x) * 180.f / 3.14159265f;
    t->RotateBy(angle);

    auto rb =
        sword->AddComponent<GameEngine::Rigidbody>();
    sf::Vector2f dir = dto.data.direction;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0.f)
        dir /= len;

    rb->velocity = dir * speed;
    rb->mass = 5;
    //rb->isKinematic = true;

    auto attack =
        sword->AddComponent<AttackComponent>(Wtype);
    auto collider =
        sword->AddComponent<BoxCollisionAttackDetector>();
    collider->size = {8, 4};

}

void Roguelike::WeaponFactory::SlowSword(
    GameEngine::Scene& scene, 
    CreateWeapon data)
{
    Roguelike::WeaponFactory::CreaetSword(
        scene, 
        data, 
        50, 
        0.6, 
        2, 
        DamageType::Physical, 
        200,
        WeaponType::SlowSword);
}

void Roguelike::WeaponFactory::FastSword(
    GameEngine::Scene& scene, 
    CreateWeapon dto)
{
    Roguelike::WeaponFactory::CreaetSword(
        scene, dto, 10, 0.2, 2, DamageType::Physical, 300, WeaponType::FastSword);
}
