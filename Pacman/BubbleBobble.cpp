#include "BubbleBobble.h"

#include <ctime>
#include <iostream>

#include "SceneSwapper.h"

using namespace dae;

void BubbleBobble::Create()
{
	// Seed rand() with current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	SceneSwapper::GetInstance().Init();

	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "----KEYBOARD----\n\n";
	std::cout << "Use WASD to move in cardinal directions\n";
	std::cout << "Press SPACEBAR to jump\n";
	std::cout << "----CONTROLLER----\n\n";
	std::cout << "Use DPAD for cardinal direction movement\n";
	std::cout << "Press A to Jump\n";
	std::cout << "Press B to shoot a bubble\n";
	std::cout << "\n";
	std::cout << "Press F1 to skip a level\n";
	std::cout << "Press F2 to mute the audio\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";

}

