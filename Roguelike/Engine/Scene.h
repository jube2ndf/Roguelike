#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
namespace GameEngine {
	class Scene
	{
	public:
        GameObject* CreateObject()
        {
            auto obj = std::make_unique<GameObject>();
            GameObject* ptr = obj.get();

            _objects.push_back(std::move(obj));

            return ptr;
        }

        void DestroyAll()
        {
            _objects.clear();
        }

        std::vector<std::unique_ptr<GameObject>>& GetObjects()
        {
            return _objects;
        }
	private:
		std::vector <std::unique_ptr< GameObject >> _objects;
	};
}
