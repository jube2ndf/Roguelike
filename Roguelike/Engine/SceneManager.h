#pragma once
#include <memory>
#include "Scene.h"

namespace GameEngine
{
    class SceneManager
    {
    public:
        Scene& CreateScene(const std::string& name);
        void SwitchScene(const std::string& name);

        Scene* GetActiveScene();

    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> _scenes;
        Scene* _activeScene = nullptr;
    };
}