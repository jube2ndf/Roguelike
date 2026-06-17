#pragma once
#include <Engine.h>
#include <IGameLayer.h>
#include "CombatSystem.h"
#include "SceneSwitch.h"
namespace Roguelike {
	class Game
	{
	public:
		Game(Engine& engine);

		void Initialize();
		
	private:
        void switchLVLs(const SwitchScene& a);
		Engine* _engine;
		void CreateLevel1();
		std::unique_ptr<CombatSystem> _combat;
	};
}
