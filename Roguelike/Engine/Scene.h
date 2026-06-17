#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Camera.h"


namespace GameEngine {
	class ENGINE_API Scene
	{
	public:
		Scene() = default;
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		~Scene() = default;

        GameObject* CreateObject();

        void DestroyMarked();

		GameObject* FindWithTag(std::string tagName);
        std::vector<GameObject*> FindWithTags(std::string tagName);

        void DestroyAll();
		void DestroyDead();

		std::vector<GameObject*> GetDeadObjects();

		std::vector<std::unique_ptr<GameObject>>& GetObjects();

		Camera &GetCamera() { return _camera; }

		void ClearScene();

    private:
        Camera _camera;
		std::vector <std::unique_ptr< GameObject >> _objects;
	};
}
