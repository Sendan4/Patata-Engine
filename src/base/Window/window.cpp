#include <iostream>
#include <SDL.h>

#include "Core/window.hpp"

Game::Window::Window(std::string Titulo, int Width, int Height, bool GraphicsApi) {
	if (Titulo.empty())
		Titulo = "Patata Engine";

	WINDOW = SDL_CreateWindow(
		Titulo.data(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Width,
		Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!WINDOW) {
		std::cout << "SDL - Fallo la creacion de la ventana :\t" << SDL_GetError() << "\n";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana", NULL);
	}
	else SetIcon(WINDOW);
}

Game::Window::~Window(void) {
	SDL_DestroyWindow(WINDOW);
}

// Get
SDL_Window * Game::Window::Window_get(void) { return WINDOW; }

// Set
void Game::Window::Window_set(SDL_Window * Set) { WINDOW = Set; }
//SDL_GLContext Game::Window::glcontext_get(void) { return OPENGL_CONTEXT; }
