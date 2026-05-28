#pragma once
#include "SceneRequest.h"
#include "SceneType.h"
namespace Scene {
	class SceneCommand
	{
	public:
		SceneCommand() : action(SceneRequest::None), id(SceneType::None) {

		}
		SceneCommand(SceneRequest action) :
			action(action), id(SceneType::None) {

		}
		SceneCommand(SceneRequest action, SceneType id) :
			action(action), id(id) {

		}

		SceneRequest getAction() const {
			return this->action;
		}
		SceneType getId() const {
			return this->id;
		}

	private:
		SceneRequest action = SceneRequest::None;
		SceneType id = SceneType::None;
	};
}