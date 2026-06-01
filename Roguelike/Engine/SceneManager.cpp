#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

GameEngine::Scene& GameEngine::SceneManager::CreateScene(const std::string& name)
{
    auto scene = std::make_unique<Scene>();
    Scene* ptr = scene.get();

    _scenes[name] = std::move(scene);

    if (!_activeScene)
        _activeScene = ptr;

    return *ptr;
}

void GameEngine::SceneManager::SwitchScene(const std::string& name)
{
    auto it = _scenes.find(name);

    if (it == _scenes.end())
        return;

    _activeScene = it->second.get();
}

GameEngine::Scene* GameEngine::SceneManager::GetActiveScene()
{
    return _activeScene;
}
