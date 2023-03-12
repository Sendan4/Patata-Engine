#include "window.hpp"
#include <vector>
#include <SDL_vulkan.h>

Game::Window::Window(const char *Titulo, int Width, int Height, bool GraphicsApi) {
	uint32_t flags = 0;
	if (GraphicsApi)
		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
	else
		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

	WINDOW = SDL_CreateWindow(
		Titulo,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Width,
		Height,
		flags);

	if (!WINDOW) {
		std::cout << "SDL - Fallo la creacion de la ventana : " << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana", NULL);
	}
}

bool Game::Window::WindowRendererStart(void) {
	if (!WINDOW) return false;

	SDL_Renderer * Render = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

	if (!Render) {
		std::cout << "SDL - El contexto de renderizado no es valido :" << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana\nSDL - El contexto de renderizado no es valido", NULL);
		return false;
	}

	SDL_RenderClear(Render);
	SDL_RenderPresent(Render);
	return true;
} 

Game::Window::~Window(void) {
	SDL_DestroyRenderer(Render);
	SDL_DestroyWindow(WINDOW);
}

// Get
SDL_Renderer * Game::Window::Renderer_get(void) { return Render; }
SDL_Window * Game::Window::Window_get(void) { return WINDOW; }

// Set
void Game::Window::Window_set(SDL_Window * Set) { WINDOW = Set; }
void Game::Window::Renderer_set(SDL_Renderer * Set) {Render = Set; }
//SDL_GLContext Game::Window::glcontext_get(void) { return OPENGL_CONTEXT; }
