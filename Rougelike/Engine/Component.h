#pragma once
#include <iostream>
namespace Engine {
	class GameObject;

	class Component
	{
	public:
		static constexpr bool Unique = false;
		Component(GameObject* gameObject):_owner(gameObject) {

		}
		virtual ~Component() {
			std::cout << "Deleted component: " << this << std::endl;
		}

		virtual void Update(float deltaTime) {};

		GameObject* GetGameObject() const {
			return this->_owner;
		}
	protected:
		GameObject* _owner;
	};
}
