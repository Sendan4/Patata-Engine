#include <SDL.h>

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"
#include "Patata_Engine/Window.hpp"

void Patata::PatataEngine::MainLoop(void) {
	do {
		if (!MainInput()) break;

		Render();
	} while (true);
}
