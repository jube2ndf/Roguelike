#include "Game.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include <AudioManager.h>
#include <Logger.h>

Roguelike::Game::Game(Engine& engine)
{
    this->_engine = &engine;
}

void Roguelike::Game::Initialize()
{
    
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
    Wall::CreateWall(scene, { 0, 0 }, { 20, 600 });
    Wall::CreateWall(scene, { 780, 0 }, { 20, 600 });
    Enemy::Create(scene, { 1100, 600 });
}
