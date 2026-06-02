#include <Engine.h>
#include "Game.h"

int main()
{
	Engine engine;
	Roguelike::Game game{ engine };
	game.Initialize();
	engine.Run();
}