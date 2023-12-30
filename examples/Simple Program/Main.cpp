#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <PatataEngine/PatataEngine.hpp>

int main(int argc, char ** argv) {
	Patata::Engine Patata;

    SDL_Window * window = SDL_CreateWindow(
		#if defined(DEBUG)
		"Patata Engine | Debug (Development)",
		#else
		"Patata Engine",
		#endif
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        Patata.GetWindowFlags());

	// Window Icon
	// Esta es una fuente de errores en linux
	/*{
		SDL_Surface * Icon = SDL_LoadBMP(strcat(SDL_GetBasePath(), PATATA_GAME_ICON_FILE));
		SDL_SetWindowIcon(window ,Icon);
		SDL_FreeSurface(Icon);
	}*/

	SDL_GLContext * context = nullptr;
 
	Patata.Info->pWindow = window;
	Patata.Info->pOpenGLContext = context;

	Patata.InitRenderer();

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

	SDL_DestroyWindow(window);
	return 0;
}
