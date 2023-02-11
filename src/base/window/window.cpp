#include "window.hpp"

void Window::createWindowAndRender(void) {
	WINDOW = SDL_CreateWindow(
			"Patata Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1280, 720,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

	RENDER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
}

void Window::deleteWindowAndRender(void) {
	SDL_DestroyRenderer(RENDER);
	SDL_DestroyWindow(WINDOW);
}
