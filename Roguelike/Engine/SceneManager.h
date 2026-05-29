#pragma once
#include <memory>
#include "Scene.h"

namespace GameEngine
{
    class SceneManager
    {
    public:
        void LoadScene(std::unique_ptr<Scene> newScene)
        {
            _activeScene = std::move(newScene);
        }

        Scene* GetActiveScene()
        {
            return _activeScene.get();
        }

        bool HasScene() const
        {
            return _activeScene != nullptr;
        }

        void UnloadScene()
        {
            _activeScene.reset();
        }

    private:
        std::unique_ptr<Scene> _activeScene;
    };
}