#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
namespace GameEngine {
	class ENGINE_API Scene
	{
	public:
        GameObject* CreateObject()
        {
            auto obj = std::make_unique<GameObject>();
            GameObject* ptr = obj.get();

            _objects.push_back(std::move(obj));

            return ptr;
        }

        void DestroyMarked()
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
