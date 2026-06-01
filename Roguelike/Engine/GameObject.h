#pragma once
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "Component.h"
#include "TransformComponent.h"
namespace GameEngine {
	class ENGINE_API GameObject
	{
	public:
		GameObject() {
			this->_components.push_back(std::make_unique<TransformComponent>(this));
			std::cout << "Create object" << "\n";
		}
		~GameObject()
		{
			
		}
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		//void Update(float deltaTime);

		/// Remove all T type Component
		template<typename T>
		void RemoveComponents() {
			_components.erase(
				std::remove_if(
					_components.begin(),
					_components.end(),
					[](const auto& component)
					{
						return dynamic_cast<T*>(component.get()) != nullptr;
					}),
				_components.end());
		}
		// Remove first T type Component
		template<typename T>
		void RemoveComponent()
		{
			auto it = std::find_if(
				_components.begin(),
				_components.end(),
				[](const auto& component)
				{
					return dynamic_cast<T*>(component.get()) != nullptr;
				});

			if (it != _components.end())
			{
				_components.erase(it);
			}
		}
		// Remove T type Component
		template<typename T>
		void RemoveComponent(Component* target)
		{
			auto it = std::find_if(
				_components.begin(),
				_components.end(),
				[target](const auto& component)
				{
					return component.get() == target;
				});

			if (it != _components.end())
			{
				_components.erase(it);
			}
		}

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

			std::unique_ptr<T> component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* ptr = component.get();
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

		template<typename T>
		std::vector<T*> GetComponents() const
		{
			std::vector<T*> result;

			for (const auto& component : _components)
			{
				if (auto ptr = dynamic_cast<T*>(component.get()))
				{
					result.push_back(ptr);
				}
			}

			return result;
		}

		bool IsAlive() const { return _alive; }

		void Destroy()
		{
			_alive = false;
		}

	protected:
		std::vector<std::unique_ptr<Component>> _components;
		bool _alive = true;
	};
}