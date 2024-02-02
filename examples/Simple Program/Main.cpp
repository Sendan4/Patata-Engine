#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <PatataEngine/PatataEngine.hpp>

int main(int argc, char ** argv) {
	Patata::Engine Patata("", 1280, 720);

	bool run = true;
	while(run) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			// Patata Events
			Patata.HandleEvent(event);
			// Your Events
			if (event.type == SDL_QUIT) {
				run = false;
				break;
			}
		}

		// Your Render Functions

		Patata.Render();
	}

	return 0;
}
