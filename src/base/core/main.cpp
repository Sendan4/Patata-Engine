#include "init.hpp"
#include "window.hpp"
#include "GameMainLoop.hpp"
#include "Events.hpp"

int main(int argc, char **argv) {
    initSDL();

	Window MainWindow;

	MainWindow.start();

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;
	} while (true);

	MainWindow.finish();

	SDL_Quit();
    return 0;
}
