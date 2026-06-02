#include "pch.h"
#include "Scene.h"
#include "TagComponent.h"

GameEngine::GameObject* GameEngine::Scene::CreateObject()
{
    auto obj = std::make_unique<GameObject>();
    GameObject* ptr = obj.get();

    _objects.push_back(std::move(obj));

    return ptr;
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

GameEngine::GameObject* GameEngine::Scene::FindWithTag(std::string tagName)
{
    for (int i = 0;
        i < this->_objects.size();
        i++) 
    {
        auto tag = this->_objects[i]->GetComponent<TagComponent>();
        if (tag && tag->GetTag() == tagName) {
            return this->_objects[i].get();
        }
    }
    return nullptr;
}

void GameEngine::Scene::DestroyAll()
{
    _objects.clear();
}

std::vector<std::unique_ptr<GameEngine::GameObject>>& GameEngine::Scene::GetObjects()
{
    return _objects;
}
