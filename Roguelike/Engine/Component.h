#pragma once
#include "Engine.h"
#include <iostream>
namespace GameEngine {
	class GameObject;

	class ENGINE_API Component
	{
	public:
		static constexpr bool Unique = false;
		static constexpr bool Required = false;
		Component(GameObject* gameObject):_owner(gameObject) {
			std::cout << "Created component: "
				<< this
				<< std::endl;
		}
		virtual ~Component() {
			std::cout << "Deleted component: " << this << std::endl;
		}

		virtual void Update(float deltaTime) {};

		GameObject* GetGameObject() const {
			return this->_owner;
		}
		bool IsActive() const
		{
			return this->_active;
		}

		void SetActive(bool active)
		{
			this->_active = active;
		}
	protected:
		GameObject* _owner;
		bool _active = true;
	};
}
