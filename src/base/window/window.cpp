#include "window.hpp"

void Window::start(void) {
	WINDOW = SDL_CreateWindow(
			"Patata Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1280, 720,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

	RENDER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

	SURFACE = SDL_GetWindowSurface(WINDOW);

	if (!WINDOW) {
		std::cout << "SDL - Fallo la creacion de la ventana : " << SDL_GetError() << std::endl;
		if (!RENDER) {
			std::cout << "SDL - El contexto de renderizado no es valido :" << SDL_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana\nSDL - El contexto de renderizado no es valido", NULL);
		}
		else
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana", NULL);
	}

	SDL_RenderClear(RENDER);
	SDL_RenderPresent(RENDER);
}

void Window::finish(void) {
	SDL_DestroyRenderer(RENDER);
	SDL_DestroyWindow(WINDOW);
}

SDL_Renderer * Window::renderer_get(void) { return RENDER; }
