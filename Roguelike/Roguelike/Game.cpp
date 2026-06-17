#include "Game.h"
#include "Enemy.h"
#include "Maze.h"
#include "Player.h"
#include "Wall.h"
#include "DoorLVL.h"
#include <TransformComponent.h>
#include <AudioManager.h>
#include <EventBus.h>
#include <Logger.h>
#include "EventDieBoss.h"

Roguelike::Game::Game(Engine &engine) {
  this->_engine = &engine;
  this->_combat = std::make_unique<CombatSystem>();
}

void Roguelike::Game::Initialize() {
  GameEngine::EventBus::Subscribe<CombatAction>([this](const CombatAction &a) {
    LOG_INFO("CombatSystem", "Add action");
    this->_combat->QueueAction(a);
  });

    GameEngine::EventBus::Subscribe<SwitchScene>([this](const SwitchScene& a) {
        LOG_INFO("Scene", "Edit current scene");
        this->switchLVLs(a);
    });
  GameEngine::EventBus::Subscribe<BossDiedEvent>([this](const BossDiedEvent& a) {
      LOG_INFO("Game", "Boss die");
        auto scene = this->_engine->GetSceneManager().GetActiveScene();
        if (scene->FindWithTags("Boss").size() && scene->FindWithTags("Door").size())
        {
            for (auto iterDoor : scene->FindWithTags("Door"))
            {
                DoorTrigget* tr = iterDoor->GetComponent<DoorTrigget>();
                tr->OpenDoor();
            }
        }
  });
  this->_engine->AddLayer(this->_combat.get());
  GameEngine::AudioManager::Initialize();
  GameEngine::AudioManager::PlayMusic("./Resources/Music/fon.ogg", true);
  this->_engine->Initialize();
  this->CreateLevel1();
  this->_engine->GetSceneManager().SwitchScene("Level1");
}

void Roguelike::Game::switchLVLs(const SwitchScene& a)
{
    if (a.openedLVL == "next")
    {
        auto scene = this->_engine->GetSceneManager().GetActiveScene();
        scene->ClearScene();
        this->_engine->ClearCollision();
        Maze maze;
        for (auto& p : maze.CreateMaze(8, 5, 6))
            Wall::CreateWall(*scene, p, {32.f, 32.f});

        if (scene->FindWithTag("Player"))
        {
            auto pos = maze.FindFreeCellPlayer();
            auto player = scene->FindWithTag("Player");
            player->GetComponent<GameEngine::TransformComponent>()
                ->SetWorldPosition(pos);
        }
        Enemy::Create(*scene, maze.FindFreeCellEnemy());

        Door::Create(*scene, "next", maze.FindFreeCellDoor(), {32.f, 32.f});

    }
}

void Roguelike::Game::CreateLevel1()
{
  auto &scene = this->_engine->GetSceneManager().CreateScene("Level1");
  Maze maze;
  for (auto &p : maze.CreateMaze(8, 5, 6))
    Wall::CreateWall(scene, p, {32.f, 32.f});
  
  Player::Create(scene, maze.FindFreeCellPlayer());
  Enemy::Create(scene, maze.FindFreeCellEnemy());
  auto door = Door::Create(scene, "next", maze.FindFreeCellDoor(), {32.f, 32.f});
}
