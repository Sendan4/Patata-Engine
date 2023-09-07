#include <SDL.h>

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"

bool Patata::PatataEngine::MainInput(void) {
	SDL_PollEvent(MainEvent);

	switch (MainEvent->type) {
		case SDL_QUIT:	return false; break;
	}
	return true;
}
