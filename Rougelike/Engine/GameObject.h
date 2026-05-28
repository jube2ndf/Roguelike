#pragma once
#include <vector>
#include <cassert>
#include "Component.h"
#include "TransformComponent.h"
namespace Engine {
	class GameObject
	{
	public:
		GameObject() {
			this->_components.push_back(std::make_unique<TransformComponent>(this));
		}
		~GameObject()
		{
			
		}

		//void Update(float deltaTime);
		
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			static_assert(std::is_base_of_v<Component, T>,
				"T must inherit from Component");

			if constexpr (T::Unique)
			{
				if (GetComponent<T>() != nullptr)
				{
					std::cout << "Unique component already exists!" << std::endl;
					return nullptr;
				}
			}

			std::unique_ptr<T> component = std::make_unique<T>();
			Component* ptr = component.get();
			this->_components.push_back(std::move(component));
			return ptr;
		}

		template<typename T>
		T* GetComponent()
		{
			for (auto& component : this->_components)
			{
				if (auto ptr = dynamic_cast<T*>(component.get()))
				{
					return ptr;
				}
			}

			return nullptr;
		}

	protected:
		std::vector<std::unique_ptr<Component>> _components;
	};
}