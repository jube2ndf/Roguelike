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
#include "RotatingProjectileComponent.h"

std::unordered_map<Roguelike::WeaponType, float>
    Roguelike::WeaponFactory::culDown = {
        {Roguelike::WeaponType::SlowSwordProjectile,
         1.5},
        {Roguelike::WeaponType::FastSwordProjectile,
         0.5},
        {Roguelike::WeaponType::SwordsRotating,
         12.f},
        {Roguelike::WeaponType::FireBallRotating,
         10.f},
        {Roguelike::WeaponType::FireBallFast,
         1.f},
};

void Roguelike::WeaponFactory::Create(GameEngine::Scene& scene, CreateWeapon data)
{
    switch (data.type)
    {
    case Roguelike::WeaponType::SlowSwordProjectile:
        WeaponFactory::SlowSword(scene, data);
        break;
    case Roguelike::WeaponType::FastSwordProjectile:
        WeaponFactory::FastSword(scene, data);
        break;
    case Roguelike::WeaponType::SwordsRotating:
        WeaponFactory::SwordsRotating(scene, data);
        break;
    case Roguelike::WeaponType::FireBallRotating:
        WeaponFactory::FireBallRotating(scene, data);
        break;
    case Roguelike::WeaponType::FireBallFast:
        WeaponFactory::FireBallFast(scene, data);
        break;
    default:
        break;
    }
}

void Roguelike::WeaponFactory::CreaetSword(
    GameEngine::Scene& scene,
    CreateWeapon dto,
    float damage,
    float critChance,
    float critMultiplier,
    Damage::Context type,
    float speed,
    WeaponType Wtype,
    sf::Vector2f size,
    std::string spritTexture)
{
    GameEngine::GameObject* sword =
        scene.CreateObject();
    sword->AddComponent<GameEngine::TagComponent>("DamageSword");
    auto projectileComponent = sword->AddComponent<ProjectileComponent>(
        damage,
        critChance,
        critMultiplier,
        type,
        dto.source);

    auto rend = sword->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load(spritTexture));
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
    // rb->isKinematic = true;

    auto attack =
        sword->AddComponent<AttackComponent>(Wtype);
    auto collider =
        sword->AddComponent<BoxCollisionAttackDetector>();
    collider->size = size;
}

void Roguelike::WeaponFactory::CreaetSwordsRotating(GameEngine::Scene& scene, CreateWeapon dto, float damage, float critChance, float critMultiplier, Damage::Context type, float speed, WeaponType Wtype, sf::Vector2f size, std::string spritTexture)
{
    for (int i = 0; i < 4; i++)
    {
        GameEngine::GameObject* sword =
            scene.CreateObject();

        sword->AddComponent<GameEngine::TagComponent>("DamageSword");
        auto projectileComponent = sword->AddComponent<RotatingProjectileComponent>(
            damage,
            critChance,
            critMultiplier,
            type,
            dto.source);

        projectileComponent->angle = 90 * i;
        projectileComponent->lifeTime = 10.f;
        auto t = sword->GetComponent<GameEngine::TransformComponent>();
        t->SetWorldPosition(dto.data.position);
        
        
        float angle = std::atan2(dto.data.direction.y, dto.data.direction.x) * 180.f / 3.14159265f;
        t->RotateBy(angle);

        auto rend = sword->AddComponent<GameEngine::SpriteRenderer>(GameEngine::TextureManager::load(spritTexture));
        rend->sortingLayer = 10;

        auto rb =
            sword->AddComponent<GameEngine::Rigidbody>();
        sf::Vector2f dir = dto.data.direction;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0.f)
            dir /= len;

        auto attack =
            sword->AddComponent<AttackComponent>(Wtype);
        auto collider =
            sword->AddComponent<BoxCollisionAttackDetector>();
        collider->size = size;
        collider->mask &= ~CollisionLayers::GameObject;

        if (auto box = dto.source->GetComponent<GameEngine::BoxCollider>())
        {
            projectileComponent->radius = box->GetRadius() * 1.5f;
        }
    }
}

void Roguelike::WeaponFactory::SlowSword(
    GameEngine::Scene& scene,
    CreateWeapon data)
{
    Damage::Context type;
    type.damageType = DamageType::Physical;
    Roguelike::WeaponFactory::CreaetSword(
        scene,
        data,
        50,
        0.6,
        2,
        type,
        200,
        WeaponType::SlowSwordProjectile,
        {8, 4},
        "./Resources/Textures/sword.png");
}

void Roguelike::WeaponFactory::FastSword(
    GameEngine::Scene& scene,
    CreateWeapon dto)
{
    Damage::Context type;
    type.damageType = DamageType::Physical;
    Roguelike::WeaponFactory::CreaetSword(
        scene, dto, 10, 0.2, 2, type, 300, WeaponType::FastSwordProjectile,
        {8, 4},
        "./Resources/Textures/sword.png");
}

void Roguelike::WeaponFactory::SwordsRotating(GameEngine::Scene& scene, CreateWeapon dto)
{
    Damage::Context type;
    type.damageType = DamageType::Physical;
    Roguelike::WeaponFactory::CreaetSwordsRotating(
        scene, dto, 30, 0.2, 2, type, 50, WeaponType::SwordsRotating,
        {8, 4},
        "./Resources/Textures/sword.png");
}

void Roguelike::WeaponFactory::FireBallRotating(GameEngine::Scene& scene, CreateWeapon dto)
{
    Damage::Context type;
    type.damageType = DamageType::Elementary;
    Roguelike::WeaponFactory::CreaetSwordsRotating(
        scene, dto, 75, 0.2, 2, type, 100, WeaponType::SwordsRotating,
        {8, 8},
        "./Resources/Textures/fireball.png");
}

void Roguelike::WeaponFactory::FireBallFast(GameEngine::Scene& scene, CreateWeapon dto)
{
    Damage::Context type;
    type.damageType = DamageType::Elementary;
    Roguelike::WeaponFactory::CreaetSword(
        scene, dto, 40, 0.6, 2, type, 150, WeaponType::FireBallFast,
        {8, 8},
        "./Resources/Textures/fireball.png");
}
