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

		SceneRequest getAction() {
			return this->action;
		}
		SceneType getId() {
			return this->id;
		}

	private:
		SceneRequest action;
		SceneType id;
	};
}