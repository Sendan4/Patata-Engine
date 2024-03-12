#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <PatataEngine/PatataEngine.hpp>

int main(int argv, char ** args) {
	Patata::Engine Patata("", 1280, 720);

	while(true) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			// Patata Events
			Patata.HandleEvent(event);
			// Your Events
			if (event.type == SDL_QUIT) {
				goto FINISHLOOP;
			}
		}

		// Your Render Functions

		Patata.Render();
	}
FINISHLOOP:

	return 0;
}
