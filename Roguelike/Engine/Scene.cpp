#include "pch.h"
#include "Scene.h"


GameEngine::GameObject* GameEngine::Scene::CreateObject()
{
	return nullptr;
}

void GameEngine::Scene::DestroyMarked()
{
    _objects.erase(
        std::remove_if(
            _objects.begin(),
            _objects.end(),
            [](const std::unique_ptr<GameObject>& obj)
            {
                return !obj->IsAlive();
            }),
        _objects.end());
}

void GameEngine::Scene::DestroyAll()
{
    _objects.clear();
}

std::vector<std::unique_ptr<GameEngine::GameObject>>& GameEngine::Scene::GetObjects()
{
    return _objects;
}
