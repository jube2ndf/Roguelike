#include "Game.h"
#include "Player.h"
#include "Wall.h"

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
    Player::Create(scene, { 1280/2, 720/2 });
    Wall::CreateWall(scene, { 0, 0 }, { 800, 20 });   // верх
    Wall::CreateWall(scene, { 0, 580 }, { 800, 20 }); // низ
    Wall::CreateWall(scene, { 0, 0 }, { 20, 600 });   // лево
    Wall::CreateWall(scene, { 780, 0 }, { 20, 600 }); // право
}
