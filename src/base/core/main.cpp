#include "init.hpp"
#include "window.hpp"
#include "Events.hpp"
#include <SDL.h>

int main(int argc, char **argv) {
    initSDL();

	Window MainWindow;

	MainWindow.start();

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;

		SDL_RenderClear(MainWindow.renderer_get());
		SDL_RenderPresent(MainWindow.renderer_get());
	} while (true);

	MainWindow.finish();

	SDL_Quit();
    return 0;
}
