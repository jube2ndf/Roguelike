#include "Game.h"
#include "Player.h"

Roguelike::Game::Game(Engine& engine)
{
    this->_engine = &engine;
}

void Roguelike::Game::Initialize()
{
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
    Player::Create(scene);
}
