#pragma once
#include <memory>
#include "Scene.h"

namespace GameEngine
{
    class SceneManager
    {
    public:
        Scene& CreateScene();
        void SwitchScene(int id);

        Scene& GetActiveScene();

    private:
        std::vector<std::unique_ptr<Scene>> _scenes;
        Scene* _activeScene = nullptr;
    };
}