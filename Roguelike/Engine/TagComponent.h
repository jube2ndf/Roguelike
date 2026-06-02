#pragma once
#include "EngineAPI.h"
#include "Component.h"
#include "GameObject.h"
#include <string>
namespace GameEngine {
	class ENGINE_API TagComponent :
		public Component {
	public:
		TagComponent(GameObject* owner, std::string name) :
			Component(owner),
			_tag(name)
		{
			
		}

		std::string GetTag() {
			return this->_tag;
		}
		
	private:
		std::string _tag;
	};
}