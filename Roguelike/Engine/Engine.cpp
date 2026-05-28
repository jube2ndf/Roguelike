#include "pch.h"
#include "Engine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <iostream>
#include <windows.h>

Engine::Engine()
{
	
}

void Engine::Initialize()
{
	std::cout << "Engine initialized\n";
}

void Engine::Run()
{
	OutputDebugStringA("=== Engine::Run START ===\n");
	std::cout << "Engine create\n";
	GameEngine::GameObject obj;
	std::cout << "Engine run\n";
}
