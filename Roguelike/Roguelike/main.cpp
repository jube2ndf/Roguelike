#include <Engine.h>
#include "Game.h"

int main()
{
	srand(time(nullptr));
	Engine engine;
	Roguelike::Game game{ engine };
	game.Initialize();
	engine.Run();
}