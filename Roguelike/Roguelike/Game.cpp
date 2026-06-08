#include "Game.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include <AudioManager.h>
#include <Logger.h>
#include <EventBus.h>

Roguelike::Game::Game(Engine& engine)
{
    this->_engine = &engine;
    this->_combat = std::make_unique<CombatSystem>();
}

void Roguelike::Game::Initialize()
{
    GameEngine::EventBus::Subscribe<CombatAction>(
        [this](const CombatAction& a)
        {
            LOG_INFO("CombatSystem", "Add action");
            this->_combat->QueueAction(a);
        }
    );
    this->_engine->AddLayer(this->_combat.get());
    GameEngine::AudioManager::Initialize();
    GameEngine::AudioManager::PlayMusic("./Resources/Music/fon.ogg", true);
    this->_engine->Initialize();
    this->CreateLevel1();
    this->_engine->GetSceneManager()
        .SwitchScene("Level1");
}

void Roguelike::Game::CreateLevel1()
{
    auto& scene =
        this->_engine->GetSceneManager()
        .CreateScene("Level1");
    Player::Create(scene, { 1280/2, 720/2 });
    Wall::CreateWall(scene, { 1280 / 2, 0 }, { 1280, 40 });
    Wall::CreateWall(scene, { 1280 / 2, 720 }, { 1280, 40 });
    Wall::CreateWall(scene, { 0, 720/2 }, { 40, 720 });
    Wall::CreateWall(scene, { 1280, 720 / 2 }, { 40, 720 });
    Enemy::Create(scene, { 1100, 600 });
}
