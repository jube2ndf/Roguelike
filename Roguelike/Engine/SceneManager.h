#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

namespace GameEngine
{
    class ENGINE_API SceneManager
    {
    public:
        SceneManager() = default;

        Scene& CreateScene(const std::string& name);
        void SwitchScene(const std::string& name);

        Scene* GetActiveScene();

        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;

    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> _scenes;
        Scene* _activeScene = nullptr;
    };
}