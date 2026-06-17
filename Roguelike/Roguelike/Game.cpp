#include "Game.h"
#include "Enemy.h"
#include "Maze.h"
#include "Player.h"
#include "Wall.h"
#include <AudioManager.h>
#include <EventBus.h>
#include <Logger.h>

Roguelike::Game::Game(Engine &engine) {
  this->_engine = &engine;
  this->_combat = std::make_unique<CombatSystem>();
}

void Roguelike::Game::Initialize() {
  GameEngine::EventBus::Subscribe<CombatAction>([this](const CombatAction &a) {
    LOG_INFO("CombatSystem", "Add action");
    this->_combat->QueueAction(a);
  });
  this->_engine->AddLayer(this->_combat.get());
  GameEngine::AudioManager::Initialize();
  GameEngine::AudioManager::PlayMusic("./Resources/Music/fon.ogg", true);
  this->_engine->Initialize();
  this->CreateLevel1();
  this->_engine->GetSceneManager().SwitchScene("Level1");
}

void Roguelike::Game::CreateLevel1() {
  auto &scene = this->_engine->GetSceneManager().CreateScene("Level1");
  Maze maze;
  for (auto &p : maze.CreateMaze(8, 5, 6))
    Wall::CreateWall(scene, p, {32.f, 32.f});
  
  Player::Create(scene, maze.FindFreeCellPlayer());
  Enemy::Create(scene, maze.FindFreeCellEnemy());
}
