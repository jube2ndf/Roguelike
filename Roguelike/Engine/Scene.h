#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
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

        void DestroyAll();

		std::vector<std::unique_ptr<GameObject>>& GetObjects();

		
	private:
		std::vector <std::unique_ptr< GameObject >> _objects;
	};
}
