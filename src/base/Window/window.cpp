#include "window.hpp"

Game::Window::Window(const char *Titulo, int Width, int Height) {
	WINDOW = SDL_CreateWindow(
			Titulo,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			Width, Height,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

	RENDER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

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

Game::Window::~Window(void) {
	SDL_DestroyRenderer(RENDER);
	SDL_DestroyWindow(WINDOW);
}

// Get
SDL_Renderer * Game::Window::Renderer_get(void) { return RENDER; }
SDL_Window * Game::Window::Window_get(void) { return WINDOW; }
//SDL_GLContext Game::Window::glcontext_get(void) { return OPENGL_CONTEXT; }
